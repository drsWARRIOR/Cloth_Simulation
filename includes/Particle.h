#pragma once

#include "Constraint.h"

#include <algorithm>

/**
 * @class Particle
 * @brief Represents a point mass in the cloth simulation.
 *
 * Simulates motion using Verlet integration, supports pinning, constraints, and mouse interaction.
 */
class Particle
{
private:
    /**
     * @brief Pointers to the horizontal and vertical constraints connected to this particle.
     *
     * Index 0 = horizontal, Index 1 = vertical.
     */
    Constraint* m_constraints[2] = {nullptr};

    /**
     * @brief Current position of the particle in the simulation.
     */
    sf::Vector2f m_pos;

    /**
     * @brief Previous position of the particle.
     *
     * Used for Verlet integration to calculate velocity implicitly.
     */
    sf::Vector2f m_lastPos;

    /**
     * @brief Initial (pinned) position of the particle.
     *
     * Used to reset pinned particles to their start location.
     */
    sf::Vector2f m_startPos;

    /**
     * @brief Whether this particle is fixed in space and does not move.
     */
    bool m_isPinned = false;

    /**
     * @brief Whether this particle is currently selected by the user.
     *
     * Can be used to apply visual highlighting or special interactions.
     */
    bool m_isSelected = false;

    /**
     * @brief Whether this particle is active in the simulation.
     *
     * Inactive particles are skipped in updates and rendering.
     */
    bool m_isActive = true;

    /**
     * @brief Keeps the particle within the window bounds.
     *
     * @param width Width of the window.
     * @param height Height of the window.
     */
    void StayInBoundaries(int width, int height);

public:
    /**
     * @brief Default constructor.
     */
    Particle() = default;

    /**
     * @brief Constructs a particle at the given position.
     *
     * @param x X-coordinate of the particle.
     * @param y Y-coordinate of the particle.
     */
    Particle(float x, float y);

    /**
     * @brief Default destructor.
     */
    ~Particle() = default;

    /**
     * @brief Assigns a constraint to this particle.
     *
     * @param constraint Pointer to the constraint to assign.
     * @param index 0 for horizontal, 1 for vertical.
     */
    void AddConstraint(Constraint* constraint, int index);

    /**
     * @brief Gets the current position of the particle.
     *
     * @return Reference to the position vector.
     */
    const sf::Vector2f& GetPos();

    /**
     * @brief Sets the particle's current position.
     *
     * @param x New X-coordinate.
     * @param y New Y-coordinate.
     */
    void SetPos(float x, float y);

    /**
     * @brief Pins the particle to its current position.
     */
    void Pin();

    /**
     * @brief Updates the particle's position using Verlet integration.
     *
     * Also handles mouse interaction and applies gravity, drag, and boundary constraints.
     *
     * @param deltaTime Time since the last frame (in seconds).
     * @param win Reference to the SFML window (for input detection).
     * @param mousePos Current mouse position.
     * @param lastMousePos Previous mouse position.
     * @param cursorSize Radius of the interaction area for selecting/dragging particles.
     * @param drag Drag coefficient to slow down particle motion.
     * @param acceleration Acceleration vector (e.g., gravity).
     * @param elasticity Elasticity used when correcting position.
     * @param winWidth Width of the window.
     * @param winHeight Height of the window.
     */
    void Update(float deltaTime, sf::RenderWindow& win, sf::Vector2i& mousePos, sf::Vector2i& lastMousePos, float cursorSize, float drag, const sf::Vector2f& acceleration, float elasticity, int winWidth, int winHeight);
};
