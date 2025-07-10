#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"


/**
 * @class Core
 * @brief Abstract base class representing the core loop of an SFML application.
 *
 * Provides a structured interface for creating game or simulation loops with
 * lifecycle hooks: Begin, FixedUpdate, Update, and Render. Inheriting classes
 * must implement these virtual methods.
 */
class Core
{
private:
    /**
     * @brief The target frame rate of the application loop.
     *
     * Used to control rendering and update timing.
     */
    int m_frameRate = 60;

protected:
    /**
     * @brief Called once before the main loop begins.
     *
     * Override this to initialize simulation data, load resources, etc.
     */
    virtual void Begin() = 0;

    /**
     * @brief Called at fixed time intervals, independent of frame rate.
     *
     * Ideal for physics updates or time-consistent logic.
     *
     * @param fixedDeltaTime The fixed time step duration (in seconds).
     */
    virtual void FixedUpdate(float fixedDeltaTime) = 0;

    /**
     * @brief Called once per frame to update variable time-based logic.
     *
     * Suitable for animations, input handling, UI transitions, etc.
     *
     * @param deltaTime The elapsed time since the last frame (in seconds).
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * @brief Called once per frame to render visual output.
     *
     * Called after Update and before the next frame is displayed.
     */
    virtual void Render() = 0;

public:
    /**
     * @brief The main SFML render window.
     *
     * Inheriting classes may use this for rendering objects, handling input, etc.
     */
    sf::RenderWindow win;

    /**
     * @brief Font used for UI or debug text.
     *
     * Should be loaded and used as needed during rendering.
     */
    sf::Font font;

    /**
     * @brief Flag that controls the application's main loop.
     *
     * Set to false to exit the loop gracefully.
     */
    bool isRunning;

    /**
     * @brief Default constructor.
     */
    Core() = default;

    /**
     * @brief Virtual destructor.
     */
    ~Core() = default;

    /**
     * @brief Starts the main application loop.
     *
     * Initializes the window, sets up frame timing, and enters the update-render loop.
     *
     * @param title Title of the window.
     * @param width Width of the window in pixels.
     * @param height Height of the window in pixels.
     */
    void Run(sf::String title, unsigned int width, unsigned int height);

    /**
     * @brief Sets the target frame rate for the application.
     *
     * Influences timing of the rendering and update logic.
     *
     * @param frameRate The desired frame rate (frames per second).
     */
    void SetFrameRate(int frameRate);
};
