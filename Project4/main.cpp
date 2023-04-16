    #include "Class/SortingClass.h"
int main() {
    SortingAlgorithms<int> sorter;
    sf::RenderWindow window(sf::VideoMode(600, 800), "Sorting algorithms visualizer");
    std::vector<SortingAlgorithmButton> sortingbuttons;
    std::vector<Button> buttons;



    const int array_size = 100;
    std::vector<int> arr(array_size);


    for (int i = 0; i < array_size; i++) {
        arr[i] = rand() % static_cast<int>(window.getSize().y);

    }
    const float rectWidth = window.getSize().x / array_size;
    std::vector<sf::RectangleShape> rects(array_size);
    for (int i = 0;i < array_size;i++) {
        rects[i].setSize(sf::Vector2f(rectWidth, static_cast<float>(arr[i])));
        rects[i].setPosition(i * rectWidth, window.getSize().y - arr[i]);
        rects[i].setFillColor(sf::Color::White);

    }
    sf::Font font;
    font.loadFromFile("arial.ttf");
    SortingAlgorithmButton sort_button{ "Bubble Sort", [](sf::Event& event, std::vector<int>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {SortingAlgorithms<int>::bubble_sort(event,arr,size,window,rects,rectWidth);} };
    sortingbuttons.push_back(sort_button);
    SortingAlgorithmButton sort_button1{ "Insertation Sort", [](sf::Event& event, std::vector<int>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {SortingAlgorithms<int>::insertation_sort(event,arr,size,window,rects,rectWidth);} };
    sortingbuttons.push_back(sort_button1);


    for (int i = 0;i < sortingbuttons.size();i++) {
        Button button = button_creator(150, 50, 100, 100 + 75 * i, sortingbuttons[i].name, font);
        buttons.push_back(button);
    }
    for (auto& button : buttons) {
        window.draw(button.shape);
        window.draw(button.text);
    }
    window.display();



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                for (int i = 0;i < sortingbuttons.size();i++) {
                    Button button = buttons[i];
                    if (button.shape.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        sortingbuttons[i].func(event,arr, array_size,window,rects,rectWidth);
                        break;
                    }

                }
            }







        }
    }
        return 0;
    }


