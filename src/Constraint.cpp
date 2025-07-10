#include "Constraint.h"
#include "Particle.h"

// Constructor: initializes the constraint between two particles and stores the rest length
Constraint::Constraint(Particle& primary_particle, Particle& secondary_particle, float length) : p_1(primary_particle), p_2(secondary_particle), m_length(length) {}

void Constraint::Update()
{
    // Skip update if constraint is deactivated
    if (!m_isActive) { return; }

    // Get current positions of both particles
    sf::Vector2f p_1_pos = p_1.GetPos();
    sf::Vector2f p_2_pos = p_2.GetPos();

    // Calculate the vector between the two particles
    sf::Vector2f difference = p_1_pos - p_2_pos;

    // Compute the actual distance between the two particles
    float distance = difference.length();

    // Calculate how much correction is required
    float difference_factor = (m_length - distance) / distance;

    // Compute the offset to apply to each particle to restore the correct length
    sf::Vector2f offset = difference * difference_factor * 0.5f;

    // Apply the offset in opposite directions to both particles
    p_1.SetPos(p_1_pos.x + offset.x, p_1_pos.y + offset.y);
    p_2.SetPos(p_2_pos.x - offset.x, p_2_pos.y - offset.y);
}

// Sets whether this constraint is currently selected (for visual highlighting)
void Constraint::SetIsSelected(bool value) { m_isSelected = value; }

// Deactivates the constraint so it is no longer updated or rendered
void Constraint::DestroyConstraint() { m_isActive = false; }

// Returns whether this constraint is still active
bool Constraint::IsActive() { return m_isActive; }

// Returns whether this constraint is currently selected
bool Constraint::IsSelected() { return m_isSelected; }