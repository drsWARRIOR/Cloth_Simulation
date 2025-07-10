#include "Cloth.h"
#include "ClothSimulation.h"

Cloth::Cloth(int width_size, int height_size, int gap, int start_x, int start_y, float gravity, float drag, float elasticity)
{
    // Set physics parameters
    m_gravity = {0.f, gravity};   // Gravity only in positive Y-direction
    m_drag = drag;                // Air resistance factor
    m_elasticity = elasticity;    // Constraint elasticity

    // Pre-allocate space for performance
    int total_particles = (width_size + 1) * (height_size + 1);
    m_particles.reserve(total_particles);
    m_constraints.reserve(2 * total_particles); // Two constraints per particle (horizontal and vertical)

    // Create particles in a grid layout
    for (int y = 0; y <= height_size; y++)
    {
        for (int x = 0; x <= width_size; x++)
        {
            // Create a new particle at its grid position
            m_particles.emplace_back(start_x + x * gap, start_y + y * gap);
            Particle& particle = m_particles.back();

            // Add horizontal constraint to the left neighbor
            if (x != 0)
            {
                // particle added just before current added particle
                Particle& leftParticle = m_particles[m_particles.size() - 2];

                m_constraints.emplace_back(particle, leftParticle, gap);
                Constraint& c = m_constraints.back();

                // Add constraint references to both connected particles
                leftParticle.AddConstraint(&c, 0); // 0 = horizontal
                particle.AddConstraint(&c, 0);
            }

            // Add vertical constraint to the upper neighbor
            if (y != 0)
            {
                // particle at (x, y - 1) coordinates of the current (x, y) particle
                Particle& upParticle = m_particles[x + (y - 1) * (width_size + 1)];

                m_constraints.emplace_back(particle, upParticle, gap);
                Constraint& c = m_constraints.back();

                // Add constraint references to both connected particles
                upParticle.AddConstraint(&c, 1); // 1 = vertical
                particle.AddConstraint(&c, 1);
            }

            // Pin every second particle on the top row to fix the cloth in space
            if (y == 0 && x % 2 == 0)
            {
                particle.Pin();
            }
        }
    }
}

void Cloth::Update(float deltaTime, sf::RenderWindow& win, sf::Vector2i& mousePos, sf::Vector2i& lastMousePos)
{
    // Update each particle's position and apply physics
    for (Particle& particle : m_particles)
    {
        particle.Update(deltaTime, win, mousePos, lastMousePos, CURSOR_SIZE, m_drag, m_gravity, m_elasticity, WIN_WIDTH, WIN_HEIGHT);
    }

    // Enforce constraints to maintain cloth structure
    for (Constraint& constraint : m_constraints)
    {
        constraint.Update();
    }
}

void Cloth::RenderCloth(sf::RenderWindow& win)
{
    // Create a line list to draw all active constraints
    sf::VertexArray lines(sf::PrimitiveType::Lines);

    for (Constraint& constraint : m_constraints)
    {
        // Skip inactive constraints
        if (!constraint.IsActive()) continue;

        // Highlight selected constraints in red
        sf::Color color = constraint.IsSelected() ? sf::Color::Red : sf::Color::White;

        // Added the vertices of the line in vertex array
        lines.append(sf::Vertex{constraint.p_1.GetPos(), color});
        lines.append(sf::Vertex{constraint.p_2.GetPos(), color});
    }

    // Render all constraint lines to the window
    win.draw(lines);
}
