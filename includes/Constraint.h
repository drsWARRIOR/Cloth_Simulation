#pragma once

#include <cmath>
#include "SFML/Graphics/RenderWindow.hpp"

class Particle;

/**
 * @class Constraint
 * @brief Represents a spring-like connection between two particles in a cloth simulation.
 *
 * Maintains a fixed rest length between two particles and restores it during updates
 * to simulate cloth tension and elasticity.
 */
class Constraint
{
private:
    /**
     * @brief The rest length of the constraint (initial distance between the two particles).
     */
    float m_length;

    /**
     * @brief Indicates whether the constraint is visually selected (for highlighting).
     */
    bool m_isSelected = false;

    /**
     * @brief Determines whether this constraint is active in the simulation.
     */
    bool m_isActive = true;

public:
    /**
     * @brief Reference to the first particle connected by this constraint.
     */
    Particle& p_1;

    /**
     * @brief Reference to the second particle connected by this constraint.
     */
    Particle& p_2;

    /**
     * @brief Constructs a constraint between two particles with a specific rest length.
     *
     * @param primary_particle Reference to the first particle.
     * @param secondary_particle Reference to the second particle.
     * @param length The rest length of the constraint (desired distance between particles).
     */
    Constraint(Particle& primary_particle, Particle& secondary_particle, float length);

    /**
     * @brief Default destructor.
     */
    ~Constraint() = default;

    /**
     * @brief Sets whether the constraint is selected for visual feedback.
     *
     * @param value True to mark the constraint as selected; otherwise false.
     */
    void SetIsSelected(bool value);

    /**
     * @brief Updates the constraint, restoring the correct distance between particles.
     *
     * Moves both particles to enforce the rest length, unless one is pinned or inactive.
     */
    void Update();

    /**
     * @brief Disables the constraint and marks it as inactive.
     */
    void DestroyConstraint();

    /**
     * @brief Returns whether the constraint is still active in the simulation.
     *
     * @return True if active, false if destroyed.
     */
    bool IsActive();

    /**
     * @brief Returns whether the constraint is currently selected.
     *
     * @return True if selected, false otherwise.
     */
    bool IsSelected();
};