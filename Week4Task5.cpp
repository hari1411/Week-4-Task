#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Observer Pattern: ModeObserver
class ModeObserver {
public:
    virtual void update(const std::string& mode) = 0;
    virtual ~ModeObserver() = default;
};

// Singleton: HMISystem
class HMISystem {
private:
    std::string mode;
    static HMISystem* instance;
    std::vector<ModeObserver*> observers;

    HMISystem() : mode("Day") {} // Private constructor

public:
    // Get the Singleton instance
    static HMISystem* getInstance() {
        if (instance == nullptr) {
            instance = new HMISystem();
        }
        return instance;
    }

    void setMode(const std::string& newMode) {
        mode = newMode;
        notifyObservers();
    }

    std::string getMode() const {
        return mode;
    }

    // Observer management
    void addObserver(ModeObserver* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->update(mode);
        }
    }
};

// Initialize the Singleton instance
HMISystem* HMISystem::instance = nullptr;

// Observer Pattern: Concrete observers
class Button : public ModeObserver {
public:
    void update(const std::string& mode) override {
        std::cout << "Button adjusting to mode: " << mode << '\n';
    }
};

class Slider : public ModeObserver {
public:
    void update(const std::string& mode) override {
        std::cout << "Slider adjusting to mode: " << mode << '\n';
    }
};

// Factory Pattern: Control and its types
class Control {
public:
    virtual void render() const = 0;
    virtual ~Control() = default;
};

class ButtonControl : public Control {
public:
    void render() const override {
        std::cout << "Rendering Button\n";
    }
};

class SliderControl : public Control {
public:
    void render() const override {
        std::cout << "Rendering Slider\n";
    }
};

class ControlFactory {
public:
    static std::unique_ptr<Control> createControl(const std::string& type) {
        if (type == "Button") {
            return std::make_unique<ButtonControl>();
        } else if (type == "Slider") {
            return std::make_unique<SliderControl>();
        } else {
            throw std::invalid_argument("Unknown control type!");
        }
    }
};

// Strategy Pattern: Rendering behaviors
class RenderStrategy {
public:
    virtual void render() const = 0;
    virtual ~RenderStrategy() = default;
};

class Render2D : public RenderStrategy {
public:
    void render() const override {
        std::cout << "Rendering in 2D mode\n";
    }
};

class Render3D : public RenderStrategy {
public:
    void render() const override {
        std::cout << "Rendering in 3D mode\n";
    }
};

class Renderer {
    std::unique_ptr<RenderStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<RenderStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void render() const {
        if (strategy) {
            strategy->render();
        } else {
            std::cout << "No rendering strategy set!\n";
        }
    }
};

// Main Function
int main() {
    // Singleton: Get the HMI system instance
    HMISystem* hmiSystem = HMISystem::getInstance();

    // Observer Pattern: Add observers
    Button buttonObserver;
    Slider sliderObserver;
    hmiSystem->addObserver(&buttonObserver);
    hmiSystem->addObserver(&sliderObserver);

    // Factory Pattern: Create controls
    auto button = ControlFactory::createControl("Button");
    auto slider = ControlFactory::createControl("Slider");

    // Render controls
    std::cout << "\nFactory Pattern: Rendering controls\n";
    button->render();
    slider->render();

    // Change mode in Singleton (Observers notified)
    std::cout << "\nObserver Pattern: Changing mode to 'Night'\n";
    hmiSystem->setMode("Night");

    // Strategy Pattern: Set rendering strategy
    Renderer renderer;
    std::cout << "\nStrategy Pattern: Using 2D rendering\n";
    renderer.setStrategy(std::make_unique<Render2D>());
    renderer.render();

    std::cout << "\nStrategy Pattern: Using 3D rendering\n";
    renderer.setStrategy(std::make_unique<Render3D>());
    renderer.render();

    return 0;
}
