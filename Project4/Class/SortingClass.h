#include <iostream>
#include <algorithm>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <chrono> 
#include <thread>
#include <future>
#include"SFML/System.hpp"
#include "SFML/OpenGL.hpp"
#include <utility>
#include <cstdlib>

#ifndef SORTINGCLASS_H
#define SORTINGCLASS_H

template <typename T>
class SortingAlgorithms {
public:
    static bool swapped;
    static bool continue_;
    static void bubble_sort(int start,int end,sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        for (start;start < size - 1 && continue_; start++) {
            for (int j = 0; j < size - start - 1 && continue_; j++) {
                event_checker(event, window);
                continue_ = window.isOpen();
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    std::cout << j << "aba" << start << std::endl;
                    swapped = true;
                }
                rects_information(j, j + 1, size, rectWidth, arr, rects, swapped, window.getSize().y);

                visualizer(window, rects, size);



            }
        }
    }

    static void insertation_sort(int start,int end,sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        int i, key, j;
        swapped = false;
        for (i = 1;i < size && continue_;i++) {
            key = arr[i];
            j = i - 1;


            while (j >= 0 && arr[j] > key && continue_) {
                arr[j + 1] = arr[j];
                j = j - 1;
                continue_ = window.isOpen();
                swapped = true;
                rects_information(i, j + 1, j + 2, size, rectWidth, arr, rects, swapped, window.getSize().y);
                visualizer(window, rects, size);
                event_checker(event, window);
            }
            arr[j + 1] = key;
            event_checker(event, window);
            continue_ = window.isOpen();


        }

    }
    static void selection_sort(int start, int end,sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        int j, min_idx;
        swapped = true;

        for (start;start < size && continue_;start++) {
            min_idx = start;
            for (j = start + 1;j < size && continue_;j++) {
                rects_information(start, j, min_idx, size, rectWidth, arr, rects, swapped, window.getSize().y);
                visualizer(window, rects, size);
                event_checker(event, window);
                continue_ = window.isOpen();

                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }

            }
            if (min_idx != start) {
                std::swap(arr[min_idx], arr[start]);
                swapped = true;

            }
        }
    }
    static void quick_sort(int start,int end,sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        if (start >= end) {
            return;
        }
        if (!continue_) {
            return;
        }
        int p = partipition(start, end, event, arr, rects, window, size, rectWidth);
        quick_sort(start, p - 1, event, arr, size, window,rects,rectWidth);
        quick_sort(p + 1, end, event, arr, size, window, rects, rectWidth);
        
        


    }
    static void merge_sort(int begin, int end, sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow &window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        if (begin >= end) {
            return;
        }
        if (!continue_) {
            return;
        }
        int mid = begin + (end - begin) / 2;
        merge_sort( begin, mid,event,arr,size,window,rects,rectWidth);
        merge_sort( mid + 1, end,event,arr,size,window,rects,rectWidth);
        merger(arr, begin, mid, end);
        swapped = true;
        rects_information(mid,begin ,end, size, rectWidth, arr, rects, swapped, window.getSize().y);
        visualizer(window, rects, size);
        event_checker(event, window);
        continue_ = window.isOpen();
    }
    static void bogo_sort(int begin, int end, sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        while (!is_not_sorted(arr, size)&& continue_) {
            shuffle(arr, size);
            swapped = true;
            event_checker(event, window);
            continue_ = window.isOpen();
            rects_information(begin, end, size, rectWidth, arr, rects, swapped, window.getSize().y);
            visualizer(window, rects, size);
        }
        event_checker(event, window);
        continue_ = window.isOpen();
        rects_information(begin, end, size, rectWidth, arr, rects, swapped, window.getSize().y);
        visualizer(window, rects, size);
    }
    static void cocktail_sorter(int begin, int end, sf::Event& event, std::vector<T>& arr, int size, sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, int rectWidth) {
        swapped = true;
        while (swapped && continue_ ) {
            swapped = false;
            for (int i = begin;i < end && continue_; i++) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                    event_checker(event, window);
                    continue_ = window.isOpen();
                    rects_information(i,i+1, size, rectWidth, arr, rects, swapped, window.getSize().y);
                    visualizer(window, rects, size);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
            swapped = false;
            end--;
            for (int i = end - 1;i >= begin; i--) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                    event_checker(event, window);
                    continue_ = window.isOpen();
                    rects_information(i, i + 1, size, rectWidth, arr, rects, swapped, window.getSize().y);
                    visualizer(window, rects, size);
                    swapped = true;
                }
            }
            begin++;
        }
    }
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
    static bool is_not_sorted(std::vector<T>& arr, int size) {
        int i = 0;
        while (i <size-1) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
            i++;
        }
        return true;
    }
    static void shuffle(std::vector<T>& arr, int size) {
        for (int i = 0;i < size;i++) {
            std::swap(arr[i], arr[rand() % size]);
        }
    }
    static int partipition( int start, int end,sf::Event& event, std::vector<T>& arr, std::vector<sf::RectangleShape>& rects, sf::RenderWindow& window,int size,int rectWidth) {
        int pivot = arr[start];
        int count = 0;
        for (int i = start + 1;i <= end&& continue_;i++) {
            if (arr[i] <= pivot) {
                count++;


            }
        }
        std::cout << pivot << std::endl;
        int pivotindex = start + count;
        std::swap(arr[pivotindex], arr[start]);
        swapped = true;
        rects_information(pivotindex, start, size, rectWidth, arr, rects, swapped, window.getSize().y);
        visualizer(window,rects,size);
        int i = start, j = end;
        std::cout << pivot << std::endl;
        while(i<pivotindex && j>pivotindex && continue_){
            while (arr[i] <= pivot && continue_){
                i++;
                std::cout << i << std::endl;
                }
            while (arr[j] > pivot && continue_) {
                j--;
                std::cout << j << std::endl;
            }
            if (i<pivotindex && j>pivotindex) {
                std::swap(arr[i++], arr[j--]);
                swapped = true;
                event_checker(event, window);
                continue_ = window.isOpen();
                rects_information(i+1,j-1, size, rectWidth, arr, rects, swapped, window.getSize().y);
                visualizer(window, rects, size);
            }
        }
        return pivotindex;


    }
    static void merger(std::vector<T>& arr,int left,int mid ,int right) {
        int subarray_1 = mid - left + 1;
        int subarray_2 = right - mid;
        std::vector<int>leftarr(subarray_1, 0);
        std::vector<int>rightarr(subarray_2, 0);
        for (int i = 0;i < subarray_1;i++) {
            leftarr[i] = arr[left + i];

        }
        for (int j = 0;j < subarray_2;j++) {
            rightarr[j] = arr[mid + 1 + j];
        }
        int indexarr1 = 0;
        int indexarr2 = 0;
        int indexmixarr = left;

        while (indexarr1 < subarray_1 && indexarr2 < subarray_2) {
            if (leftarr[indexarr1] <= rightarr[indexarr2]) {
                arr[indexmixarr] = leftarr[indexarr1];
                indexarr1++;
            }
            else {
                arr[indexmixarr] = rightarr[indexarr2];
                indexarr2++;
            }
            indexmixarr++;

        }
        while (indexarr1 < subarray_1) {
            arr[indexmixarr] = leftarr[indexarr1];
            indexmixarr++;
            indexarr1++;
        }
        while (indexarr2 < subarray_2) {
            arr[indexmixarr] = rightarr[indexarr2];
            indexarr2++;
            indexmixarr++;
        }
        leftarr.clear();
        rightarr.clear();

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
Button button_creator(int width, int height, int x, int y, const std::string& string, sf::Font& font) {
    Button button;
    button.shape.setSize(sf::Vector2f(width, height));
    button.shape.setFillColor(sf::Color::Green);
    button.shape.setPosition(x, y);
    button.text.setFont(font);


    button.text.setString(string);
    button.text.setCharacterSize(22);
    button.text.setFillColor(sf::Color::Blue);
    button.text.setPosition(button.shape.getPosition().x + 5, button.shape.getPosition().y + 10);

    return button;
}
struct SortingAlgorithmButton {
    std::string name;
    void (*func)(int,int,sf::Event&, std::vector<int>&, int, sf::RenderWindow&, std::vector<sf::RectangleShape>&, int);
};

#endif