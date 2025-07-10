#include "Particle.h"

// Constructor: initialize position, last position, and starting position to the same point
Particle::Particle(float x, float y){ m_pos = m_lastPos = m_startPos = sf::Vector2f(x, y); }

// Assigns a constraint pointer to one of the two available slots (0 = horizontal, 1 = vertical)
void Particle::AddConstraint(Constraint* constraint, int index) { m_constraints[index] = constraint; }

// Returns the current position of the particle
const sf::Vector2f& Particle::GetPos() { return m_pos; }

// Sets the current position of the particle
void Particle::SetPos(float x, float y) { m_pos.x = x; m_pos.y = y; }

// Pins the particle in place (it will not move)
void Particle::Pin() { m_isPinned = true; }

void Particle::Update(float deltaTime, sf::RenderWindow& win, sf::Vector2i& mousePos, sf::Vector2i& lastMousePos, float cursorSize, float drag, const sf::Vector2f& acceleration, float elasticity, int winWidth, int winHeight)
{
    // Skip update if the particle is inactive
    if (!m_isActive) { return; }

    // Check if the mouse is hovering over the particle (used for selection)
    sf::Vector2f mouseToPosDir = m_pos - static_cast<sf::Vector2f>(mousePos);
    float mouseToPos_length = mouseToPosDir.x * mouseToPosDir.x + mouseToPosDir.y * mouseToPosDir.y;
    m_isSelected = mouseToPos_length < cursorSize * cursorSize;

    // Highlight constraints if this particle is selected
    for (Constraint* constraint : m_constraints)
    {
        if (constraint != nullptr)
        {
            constraint->SetIsSelected(m_isSelected);
        }
    }

    // Handle left mouse drag interaction (move particle)
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isSelected)
    {
        sf::Vector2f difference = static_cast<sf::Vector2f>(mousePos - lastMousePos);

        // Clamp movement with elasticity factor to avoid unrealistic snapping
        difference.x = std::clamp(difference.x, -elasticity, elasticity);
        difference.y = std::clamp(difference.y, -elasticity, elasticity);

        // Update last position so that the Verlet step moves the particle
        m_lastPos = m_pos - difference;
    }

    // Handle right click: deactivate particle and destroy its constraints
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && m_isSelected)
    {
        m_isActive = false;

        for (Constraint* constraint : m_constraints)
        {
            if (constraint != nullptr)
            {
                constraint->DestroyConstraint();
            }
        }
    }

    // If the particle is pinned, snap it to its original position
    if (m_isPinned)
    {
        m_pos = m_startPos;
        return;
    }

    // Perform Verlet integration to update position
    sf::Vector2f newPos = m_pos + (m_pos - m_lastPos) * (1.0f - drag) + (acceleration * 100.f) * (1.0f - drag) * deltaTime * deltaTime;
    // (1 - drag) is friction or damping factor

    m_lastPos = m_pos;
    m_pos = newPos;

    // Ensure particle stays within screen bounds
    StayInBoundaries(winWidth, winHeight);
}

// Prevent particle from going outside the screen/window boundaries
void Particle::StayInBoundaries(int width, int height)
{
    if (m_pos.x > width)
    {
        m_pos.x = width;
        m_lastPos.x = m_pos.x;
    }
    else if (m_pos.x < 0)
    {
        m_pos.x = 0;
    }

    if (m_pos.y > height)
    {
        m_pos.y = height;
        m_lastPos.y = m_pos.y;
    }
    else if (m_pos.y < 0)
    {
        m_pos.y = 0;
        m_lastPos.y = m_pos.y;
    }
}