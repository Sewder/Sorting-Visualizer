#include <iostream>
#include <algorithm>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <chrono> 
#include <thread>
#include <future>
#include"SFML/System.hpp"
#include "SFML/OpenGL.hpp"

#ifndef SORTINGCLASS_H
#define SORTINGCLASS_H

template <typename T>
class SortingAlgorithms {
public:
    static bool swapped;
    static bool continue_;
    static void bubble_sort(sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        for (int ali = 0; ali < size - 1 && continue_; ali++) {
            for (int j = 0; j < size - ali - 1 && continue_; j++) {
                event_checker(event, window);
                continue_ = window_open(window);
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    std::cout << j << "aba" << ali << std::endl;
                    swapped = true;
                }
                rects_information(j, j + 1, size, rectWidth, arr, rects, swapped, window.getSize().y);

                visualizer(window, rects, size);



            }
        }
    }

    static void insertation_sort(sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        int i, key, j;
        bool swapped = false;
        for (i = 1;i < size && continue_;i++) {
            key = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j] > key && continue_) {
                arr[j + 1] = arr[j];
                j = j - 1;
                swapped = true;
                rects_information(i, j + 1, j + 2, size, rectWidth, arr, rects, swapped, window.getSize().y);
                visualizer(window, rects, size);
                event_checker(event, window);
            }
            arr[j + 1] = key;
            event_checker(event, window);


        }

    }
    static void selection_sort(T* arr, int size);
    static void visualizer(sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int array_size) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        window.clear();
        for (int i = 0; i < array_size; i++) {
            window.draw(rects[i]);
        }
        window.display();

    }
    static void rects_information(int swapped1, int swapped2, int size, int rectWidth, std::vector<T>& arr, std::vector<sf::RectangleShape>& rects, bool swapped, int windows_size_y) {
        for (int i = 0;i < size;i++) {
            rects[i].setSize(sf::Vector2f(rectWidth, static_cast<float>(arr[i])));
            rects[i].setPosition(i * rectWidth, windows_size_y - arr[i]);
            rects[i].setFillColor(sf::Color::White);
        }
        if (swapped) {
            rects[swapped2].setFillColor(sf::Color::Green);
            rects[swapped1].setFillColor(sf::Color::Red);
            swapped = false;
        }
    }
    static void rects_information(int swapped1, int swapped2, int swapped3, int size, int rectWidth, std::vector<T>& arr, std::vector<sf::RectangleShape>& rects, bool swapped, int windows_size_y) {
        for (int i = 0;i < size;i++) {
            rects[i].setSize(sf::Vector2f(rectWidth, static_cast<float>(arr[i])));
            rects[i].setPosition(i * rectWidth, windows_size_y - arr[i]);
            rects[i].setFillColor(sf::Color::White);
        }
        if (swapped) {
            rects[swapped1].setFillColor(sf::Color::Green);
            rects[swapped2].setFillColor(sf::Color::Red);
            rects[swapped3].setFillColor(sf::Color::Red);
            swapped = false;
        }
    }
    static void event_checker(sf::Event& event, sf::RenderWindow& window) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

    }
    static bool window_open(sf::RenderWindow& window) {
        if (!window.isOpen()) {
            return false;
        }
        else {
            return true;
        }
    }
}
;
template<typename T>
bool SortingAlgorithms<T>::swapped = false;

template<typename T>
bool SortingAlgorithms<T>::continue_ = true;
struct Button {
    sf::RectangleShape shape;
    sf::Text text;

};
Button button_creator(int width, int height, int x, int y, const std::string& string,sf::Font& font) {
    Button button;
    button.shape.setSize(sf::Vector2f(width, height));
    button.shape.setFillColor(sf::Color::Green);
    button.shape.setPosition(x, y);
    button.text.setFont(font);


    button.text.setString(string);
    button.text.setCharacterSize(18);
    button.text.setFillColor(sf::Color::White);
    button.text.setPosition(button.shape.getPosition().x + 5, button.shape.getPosition().y + 10);

    return button;
}
struct SortingAlgorithmButton {
    std::string name;
    void (*func)(sf::Event&, std::vector<int>&, int, sf::RenderWindow&, std::vector<sf::RectangleShape>&, int);
};

#endif