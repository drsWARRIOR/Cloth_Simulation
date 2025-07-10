#pragma once

#include "Particle.h"
#include <vector>

/**
 * @class Cloth
 * @brief Represents a 2D cloth mesh made up of particles and constraints.
 *
 * Simulates realistic cloth behavior using Verlet integration and structural constraints.
 * Can be updated and rendered per frame as part of a physics simulation.
 */
class Cloth
{
private:
    /**
     * @brief Gravity vector applied to all particles in the cloth.
     */
    sf::Vector2f m_gravity;

    /**
     * @brief Drag coefficient applied to particle velocity (simulates air resistance).
     */
    float m_drag;

    /**
     * @brief Elasticity factor that determines how much constraints can stretch or compress.
     */
    float m_elasticity;

    /**
     * @brief List of all particles making up the cloth mesh.
     */
    std::vector<Particle> m_particles;

    /**
     * @brief List of all constraints (springs) between particles.
     */
    std::vector<Constraint> m_constraints;

public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty cloth object. Use only if parameters will be set later.
     */
    Cloth() = default;

    /**
     * @brief Constructs a cloth mesh with specified dimensions and physical properties.
     *
     * @param width_size Number of particles horizontally.
     * @param height_size Number of particles vertically.
     * @param gap Distance (in pixels) between particles.
     * @param start_x X-coordinate of the top-left corner of the cloth.
     * @param start_y Y-coordinate of the top-left corner of the cloth.
     * @param gravity Magnitude of gravity to apply.
     * @param drag Air resistance factor to dampen particle movement.
     * @param elasticity Constraint stiffness (lower = more stretchy).
     */
    Cloth(int width_size, int height_size, int gap, int start_x, int start_y, float gravity, float drag, float elasticity);

    /**
     * @brief Default destructor.
     */
    ~Cloth() = default;

    /**
     * @brief Updates all particles and constraints in the cloth for the current frame.
     *
     * Handles mouse interaction, applies gravity and drag, enforces constraints, and updates positions.
     *
     * @param deltaTime Time elapsed since the last frame (in seconds).
     * @param win Reference to the SFML render window (used for coordinate conversion).
     * @param mousePos Current mouse position in window coordinates.
     * @param lastMousePos Previous mouse position (used for interaction like dragging).
     */
    void Update(float deltaTime, sf::RenderWindow& win, sf::Vector2i& mousePos, sf::Vector2i& lastMousePos);

    /**
     * @brief Renders the cloth on the SFML window.
     *
     * Draws all particles and connecting constraints.
     *
     * @param win Reference to the SFML render window.
     */
    void RenderCloth(sf::RenderWindow& win);
};
