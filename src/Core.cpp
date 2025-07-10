#include "Core.h"

void Core::Run(sf::String title, unsigned int width, unsigned int height)
{
    // Create the main application window
    win = sf::RenderWindow(sf::VideoMode({width, height}), title);

    /**
     * Load font for displaying FPS; log error if missing
     * DATA_PATH is defined in CMakeLists.txt file as target_compile_definition
     * DATA_PATH = "{CMAKE_BINARY_DIR}/bin/data/"
    **/
    if (!font.openFromFile(DATA_PATH"arial.ttf"))
    {
        std::cerr << DATA_PATH << std::endl;
    }

    isRunning = true;

    // User-defined initialization logic
    Begin();

    // Set frame rate limit for smoother visuals
    win.setFramerateLimit(m_frameRate);

    // Clock to track delta time between frames
    sf::Clock clock;
    float deltaTime;

    // Set up FPS display text
    sf::Text textFPS(font);
    textFPS.setCharacterSize(15);
    textFPS.setFillColor(sf::Color::White);

    // Fixed time step for consistent physics updates
    const float FIXED_DELTA_TIME = 1.0f / 60.0f;

    // Main application loop
    while (win.isOpen())
    {
        // Measure time since last frame
        deltaTime = clock.restart().asSeconds();

        // Update FPS counter string
        textFPS.setString("Frame Rate : " + std::to_string(1.f / deltaTime));

        // === Event Polling ===
        while (const std::optional event = win.pollEvent())
        {
            // Close window if user clicks "X" or presses Escape
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                isRunning = false;
                win.close();
            }
        }

        // === Logic Updates ===
        FixedUpdate(FIXED_DELTA_TIME); // Physics or consistent logic
        Update(deltaTime);           // Variable logic

        // === Rendering ===
        win.clear();         // Clear previous frame
        Render();            // Custom drawing logic
        win.draw(textFPS);   // Draw FPS counter
        win.display();       // Present new frame
    }
}

void Core::SetFrameRate(int framerate) { m_frameRate = framerate; /* Set the Frame Rate based on parameter input */ }
