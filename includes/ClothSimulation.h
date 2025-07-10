#pragma once

#include "Core.h"
#include "Cloth.h"

/// @brief Width of the application window in pixels.
#define WIN_WIDTH 400

/// @brief Height of the application window in pixels.
#define WIN_HEIGHT 350

/// @brief Width of the cloth mesh in simulation units.
#define CLOTH_WIDTH 240

/// @brief Height of the cloth mesh in simulation units.
#define CLOTH_HEIGHT 190

/// @brief Spacing (gap) between particles in the cloth mesh.
#define CLOTH_GAPPING 10

/// @brief Downward accleration due to gravity applied on the cloth
#define GRAVITY 9.81

/// @brief Air resistance or damping applied to particle motion.
#define DRAG 0.01

/// @brief Strength of the constraint forces keeping particles together.
#define ELASTICITY 10

/// @brief Radius of circular input that is used for interacting with cloth.
#define CURSOR_SIZE 20

/**
 * @class ClothSimulation
 * @brief Concrete class that implements a 2D cloth simulation using the Core framework.
 *
 * This class inherits from Core and overrides lifecycle methods to perform
 * initialization, update simulation state, handle user interaction, and render
 * the cloth mesh. It interacts with a Cloth object which contains the simulation data.
 */
class ClothSimulation : public Core
{
private:
    /**
     * @brief Current mouse position on the window.
     *
     * Used for interaction with the cloth (e.g., dragging particles).
     */
    sf::Vector2i m_mousePos{0, 0};

    /**
     * @brief Previous frame's mouse position.
     *
     * Useful for computing mouse drag delta.
     */
    sf::Vector2i m_mouseLastPos{0, 0};

    /**
     * @brief Pointer to the main cloth object being simulated.
     */
    Cloth* m_cloth = nullptr;

protected:
    /**
     * @brief Called once before the simulation starts.
     *
     * Initializes the cloth mesh and any necessary resources.
     */
    void Begin() override;

    /**
     * @brief Called at a fixed timestep to update physics logic.
     *
     * @param fixedDeltaTime The fixed time step duration (in seconds).
     */
    void FixedUpdate(float fixedDeltaTime) override;

    /**
     * @brief Called once per frame to update frame-based logic such as input.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds).
     */
    void Update(float deltaTime) override;

    /**
     * @brief Called once per frame to render the cloth and other visuals.
     */
    void Render() override;

public:
    /**
     * @brief Destructor to clean up cloth simulation resources.
     */
    ~ClothSimulation();
};
