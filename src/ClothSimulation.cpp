#include "ClothSimulation.h"

void ClothSimulation::Begin()
{
    // Calculate how many particles will fit in the cloth horizontally and vertically
    int width_particle_count = CLOTH_WIDTH / CLOTH_GAPPING;
    int height_particel_count = CLOTH_HEIGHT / CLOTH_GAPPING;

    // Calculate starting x and y position so that the cloth is centered horizontally
    // and positioned a bit below the top of the window
    int start_x = WIN_WIDTH * 0.5f - width_particle_count * CLOTH_GAPPING * 0.5f;
    int start_y = WIN_HEIGHT * 0.1f;

    // Create a new cloth object with the calculated parameters
    m_cloth = new Cloth(width_particle_count, height_particel_count, CLOTH_GAPPING, start_x, start_y, GRAVITY, DRAG, ELASTICITY);
}

void ClothSimulation::FixedUpdate(float fixedDeltaTime)
{
    // Update the cloth physics with a fixed time step
    m_cloth->Update(fixedDeltaTime, win, m_mousePos, m_mouseLastPos);
}

void ClothSimulation::Update(float deltaTime)
{
    // Save last frame's mouse position
    m_mouseLastPos = m_mousePos;

    // Get current mouse position relative to the window
    m_mousePos = sf::Mouse::getPosition(win);
}

void ClothSimulation::Render()
{
    // Draw the cloth onto the window
    m_cloth->RenderCloth(win);
}

ClothSimulation::~ClothSimulation()
{
    // Clean up the cloth object to free memory
    delete m_cloth;
}
