#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>

// 起泡排序
template <typename T>
void bubbleSort(T& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        for (std::size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
template <typename T>
void insertionSort(T& arr) {
    for (std::size_t i = 1; i < arr.size(); ++i) {
        auto key = arr[i];
        std::size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// 选择排序
template <typename T>
void selectionSort(T& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        std::size_t minIndex = i;
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

// 归并排序
template <typename T>
void merge(T& arr, std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t n1 = mid - left + 1;
    std::size_t n2 = right - mid;

    T L, R;
    for (std::size_t i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (std::size_t j = 0; j < n2; ++j) R[j] = arr[mid + j + 1];

    std::size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

template <typename T>
void mergeSort(T& arr, std::size_t left, std::size_t right) {
    if (left >= right) return;

    auto mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// 快速排序
template <typename T>
std::size_t partition(T& arr, std::size_t low, std::size_t high) {
    auto pivot = arr[high];
    std::size_t i = low;
    for (std::size_t j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}

template <typename T>
void quickSort(T& arr, std::size_t low, std::size_t high) {
    if (low >= high) return;

    auto pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

// 堆排序
template <typename T>
void heapify(T& arr, std::size_t n, std::size_t i) {
    auto largest = i;
    auto l = 2 * i + 1;
    auto r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(T& arr) {
    for (int i = static_cast<int>(arr.size() / 2 - 1); i >= 0; --i)
        heapify(arr, arr.size(), static_cast<std::size_t>(i));

    for (int i = static_cast<int>(arr.size() - 1); i >= 0; --i) {
        std::swap(arr[0], arr[static_cast<std::size_t>(i)]);
        heapify(arr, static_cast<std::size_t>(i), 0);
    }
}

int main() {
    constexpr std::size_t N = 10000;
    std::array<int, N> arr{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, N);

    auto testSort = [&](auto sortFunc, const char* sortName) {
        std::cout << sortName << ":\n";

        // 顺序序列
        for (std::size_t i = 0; i < N; ++i) arr[i] = static_cast<int>(i);
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

        // 逆序序列
        for (std::size_t i = 0; i < N; ++i) arr[i] = static_cast<int>(N - i - 1);
        start = std::chrono::high_resolution_clock::now();
        sortFunc(arr);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Reversed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

        // 随机序列
        for (std::size_t i = 0; i < N; ++i) arr[i] = dis(gen);
        start = std::chrono::high_resolution_clock::now();
        sortFunc(arr);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Random: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    };

    testSort(bubbleSort<decltype(arr)>, "Bubble Sort");
    testSort(insertionSort<decltype(arr)>, "Insertion Sort");
    testSort(selectionSort<decltype(arr)>, "Selection Sort");
    testSort([](auto& arr) { mergeSort(arr, 0, arr.size() - 1); }, "Merge Sort");
    testSort([](auto& arr) { quickSort(arr, 0, arr.size() - 1); }, "Quick Sort");
    testSort(heapSort<decltype(arr)>, "Heap Sort");

    return 0;
}
