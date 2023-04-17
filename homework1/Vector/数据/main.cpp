#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// ����һ��������
class Complex {
public:
    // ���캯�������Խ���ʵ�����鲿��Ҳ���Խ���һ��std::complex����
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    Complex(const std::complex<double>& c) : real(c.real()), imag(c.imag()) {}

    // ��ȡʵ�����鲿�ķ���
    double get_real() const { return real; }
    double get_imag() const { return imag; }

    // �����������ʵ�ָ�����֮��ļӼ��˳��Ȳ���
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
            real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

private:
    // ʵ�����鲿
    double real;
    double imag;
};

// ���������������������ӡ���������
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.get_real() << ", " << c.get_imag() << ")";
    return os;
}

// �������һ������ĸ������������ظ��
std::vector<Complex> generate_random_complex_vector(int size) {
    std::vector<Complex> result;
    result.reserve(size); // Ԥ����ռ䣬���Ч��
    std::random_device rd; // �����������
    std::uniform_real_distribution<double> dist(-10.0, 10.0); // ���ȷֲ�
    for (int i = 0; i < size; i++) {
        // �������ʵ�����鲿������һ������������ӵ�������
        result.emplace_back(dist(rd), dist(rd));
    }
    return result;
}

// ����һ���ȽϺ��������ڱȽ�����������ģ��ģ��ͬ������£���ʵ��Ϊ��׼��
bool compare_complex(const Complex& a, const Complex& b) {
    // ��������������ģ
    double mod_a = std::sqrt(a.get_real() * a.get_real() + a.get_imag() * a.get_imag());
    double mod_b = std::sqrt(b.get_real() * b.get_real() + b.get_imag() * b.get_imag());
    // ���ģ��ͬ���ͱȽ�ʵ��
    if (mod_a == mod_b) {
        return a.get_real() < b.get_real();
    }
    // ����ͱȽ�ģ
    return mod_a < mod_b;
}


// ����һ�����������������ڶԸ���������������ʹ�ñȽϺ�����Ϊ����
void bubble_sort(std::vector<Complex>& v, bool (*cmp)(const Complex&, const Complex&)) {
    int n = v.size(); // ��ȡ�����Ĵ�С
    bool swapped = true; // ����һ����־����ʾ�Ƿ����˽���
    while (swapped) { // ��������˽���������ѭ��
        swapped = false; // ���ñ�־Ϊfalse
        for (int i = 1; i < n; i++) { // ����������Ԫ�أ��ӵڶ�����ʼ
            if (cmp(v[i], v[i - 1])) { // �����ǰԪ�ر�ǰһ��Ԫ��С�����ݱȽϺ����Ķ���
                std::swap(v[i], v[i - 1]); // ��������Ԫ�ص�λ��
                swapped = true; // ���ñ�־Ϊtrue����ʾ�����˽���
            }
        }
        n--; // ���ٱ����ķ�Χ����Ϊ���һ��Ԫ���Ѿ���������
    }
}

// ����һ���鲢���������ڽ���������ĸ��������ϲ�Ϊһ������ĸ���������ʹ�ñȽϺ�����Ϊ����
void merge(std::vector<Complex>& v, int left, int mid, int right, bool (*cmp)(const Complex&, const Complex&)) {
    int n1 = mid - left + 1; // ������벿�ֵĴ�С
    int n2 = right - mid; // �����Ұ벿�ֵĴ�С

    std::vector<Complex> L(n1); // ����һ����ʱ���������ڴ洢��벿�ֵ�Ԫ��
    std::vector<Complex> R(n2); // ����һ����ʱ���������ڴ洢�Ұ벿�ֵ�Ԫ��

    for (int i = 0; i < n1; i++) { // ������벿�ֵ�Ԫ�ص�L��
        L[i] = v[left + i];
    }
    for (int j = 0; j < n2; j++) { // �����Ұ벿�ֵ�Ԫ�ص�R��
        R[j] = v[mid + 1 + j];
    }

    int i = 0; // ����һ��ָ�룬ָ��L�ĵ�һ��Ԫ��
    int j = 0; // ����һ��ָ�룬ָ��R�ĵ�һ��Ԫ��
    int k = left; // ����һ��ָ�룬ָ��v����߽�

    while (i < n1 && j < n2) { // ��L��R����ʣ��Ԫ��ʱ��ѭ���Ƚϲ��ϲ�
        if (cmp(L[i], R[j])) { // ���L�ĵ�ǰԪ�ر�R�ĵ�ǰԪ��С�����ݱȽϺ����Ķ���
            v[k] = L[i]; // ��L�ĵ�ǰԪ�ظ��Ƶ�v��
            i++; // �ƶ�L��ָ�뵽��һ��λ��
        }
        else { // ���L�ĵ�ǰԪ�ز���R�ĵ�ǰԪ��С
            v[k] = R[j]; // ��R�ĵ�ǰԪ�ظ��Ƶ�v��
            j++; // �ƶ�R��ָ�뵽��һ��λ��
        }
        k++; // �ƶ�v��ָ�뵽��һ��λ��
    }

    while (i < n1) { // ��L����ʣ��Ԫ��ʱ��ѭ�����Ƶ�v��
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) { // ��R����ʣ��Ԫ��ʱ��ѭ�����Ƶ�v��
        v[k] = R[j];
        j++;
        k++;
    }
}

// ����һ���鲢�����������ڶԸ���������������ʹ�ñȽϺ�����Ϊ����
void merge_sort(std::vector<Complex>& v, int left, int right, bool (*cmp)(const Complex&, const Complex&)) {
    if (left < right) { // �����߽�С���ұ߽磬˵�������Լ����ָ�
        int mid = (left + right) / 2; // �����м�λ��
        merge_sort(v, left, mid, cmp); // ����벿�ֽ��й鲢����
        merge_sort(v, mid + 1, right, cmp); // ���Ұ벿�ֽ��й鲢����
        merge(v, left, mid, right, cmp); // ����������Ĳ��ֺϲ�Ϊһ������Ĳ���
    }
}


// ����һ����ӡ���������ڴ�ӡ��������������
void print_vector(const std::vector<Complex>& v) {
    for (const auto& c : v) {
        std::cout << c << " ";
    }
    std::cout << "\n";
}

// ����һ��������Һ�����������˳��ĸ��������У����ҳ�ģ����[m1,m2) ������Ԫ�أ��������һ������������Ϊ����ֵ
std::vector<Complex> range_search(const std::vector<Complex>& v, double m1, double m2) {
    // ����һ���յ������������ڴ洢���
    std::vector<Complex> result;
    // ����ԭʼ������ÿ��Ԫ��
    for (const auto& c : v) {
        // ���㵱ǰԪ�ص�ģ
        double mod = std::sqrt(c.get_real() * c.get_real() + c.get_imag() * c.get_imag());
        // ���ģ����[m1,m2)���ͽ���ǰԪ����ӵ���������
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    // ����������
    return result;
}

// ���������в����������������ҡ����ң�ʵ�����鲿����ͬ�������롢ɾ����Ψһ���Ĳ���
int main() {
    // ����һ����СΪ10�������������
    std::vector<Complex> v = generate_random_complex_vector(10);

    // ��ӡԭʼ����
    std::cout << "ԭʼ������\n";
    for (const auto& c : v) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // ��������
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(v.begin(), v.end(), gen);

    // ��ӡ���Һ������
    std::cout << "���Һ��������\n";
    for (const auto& c : v) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // ����ָ���ĸ�����ʵ�����鲿����ͬ��
    Complex target(1.0, 2.0); // Ŀ�긴��
    auto it = std::find(v.begin(), v.end(), target); // �������в���
    if (it != v.end()) { // ����ҵ���
        std::cout << "�ҵ���Ŀ�긴�� " << target << "������λ���� " << it - v.begin() << "\n";
    }
    else { // ���û�ҵ�
        std::cout << "û���ҵ�Ŀ�긴�� " << target << "\n";
    }

    std::cout << "\n";

    // ����һ���µĸ�����������ĩβ
    Complex new_complex(3.0, 4.0); // �µĸ���
    v.push_back(new_complex); // ���뵽������ĩβ

    // ��ӡ����������
    std::cout << "������������\n";
    for (const auto& c : v) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // ɾ��һ��ָ���ĸ�����ʵ�����鲿����ͬ��
    Complex to_delete(3.0, 4.0); // Ҫɾ���ĸ���
    auto it2 = std::remove(v.begin(), v.end(), to_delete); // ɾ�����������е��ڸø�����Ԫ�أ��������µ�ĩβ������
    v.erase(it2, v.end()); // ɾ�������Ԫ��

    // ��ӡɾ���������
    std::cout << "ɾ�����������\n";
    for (const auto& c : v) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // Ψһ����������ɾ�������ظ���Ԫ�أ�ֻ����һ��
    auto it3 = std::unique(v.begin(), v.end()); // Ψһ���������������µ�ĩβ������
    v.erase(it3, v.end()); // ɾ�������Ԫ��

    // ��ӡΨһ���������
    std::cout << "Ψһ�����������\n";
    for (const auto& c : v) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // �Ƚ�˳���������������£���������͹鲢�����Ч�ʣ�clock()������ʱ��

    // ����һ����СΪ1000�ĸ�������
    std::vector<Complex> v1 = generate_random_complex_vector(1000);

    // ����һ�ݣ����ڹ鲢����
    std::vector<Complex> v2 = v1;

    // ��v1�����������򣬲���ʱ
    clock_t start1 = clock(); // ��ʼ��ʱ
    bubble_sort(v1, compare_complex); // ��������
    clock_t end1 = clock(); // ������ʱ
    double elapsed1 = (double)(end1 - start1) / CLOCKS_PER_SEC; // �����ʱ

    // ��v2���й鲢���򣬲���ʱ
    clock_t start2 = clock(); // ��ʼ��ʱ
    merge_sort(v2, 0, v2.size() - 1, compare_complex); // �鲢����
    clock_t end2 = clock(); // ������ʱ
    double elapsed2 = (double)(end2 - start2) / CLOCKS_PER_SEC; // �����ʱ

    // ��ӡ���
    std::cout << "˳�����������������ʱ: " << elapsed1 << " seconds\n"; // ��ӡ��������ĺ�ʱ
    std::cout << "˳�������Ĺ鲢�����ʱ: " << elapsed2 << " seconds\n"; // ��ӡ�鲢����ĺ�ʱ

    std::cout << "\n";

    // ��v1�������ң�����ʱ
    clock_t start3 = clock(); // ��ʼ��ʱ
    std::shuffle(v1.begin(), v1.end(), gen); // ����
    clock_t end3 = clock(); // ������ʱ
    double elapsed3 = (double)(end3 - start3) / CLOCKS_PER_SEC; // �����ʱ

    // ��v2�������ң�����ʱ
    clock_t start4 = clock(); // ��ʼ��ʱ
    std::shuffle(v2.begin(), v2.end(), gen); // ����
    clock_t end4 = clock(); // ������ʱ
    double elapsed4 = (double)(end4 - start4) / CLOCKS_PER_SEC; // �����ʱ

    std::cout << "\n";

    // ��v1�����������򣬲���ʱ
    clock_t start5 = clock(); // ��ʼ��ʱ
    bubble_sort(v1, compare_complex); // ��������
    clock_t end5 = clock(); // ������ʱ
    double elapsed5 = (double)(end5 - start5) / CLOCKS_PER_SEC; // �����ʱ

    // ��v2���й鲢���򣬲���ʱ
    clock_t start6 = clock(); // ��ʼ��ʱ
    merge_sort(v2, 0, v2.size() - 1, compare_complex); // �鲢����
    clock_t end6 = clock(); // ������ʱ
    double elapsed6 = (double)(end6 - start6) / CLOCKS_PER_SEC; // �����ʱ

    // ��ӡ���
    std::cout << "�������������������ʱ: " << elapsed5 << " seconds\n"; // ��ӡ��������ĺ�ʱ
    std::cout << "���������Ĺ鲢�����ʱ: " << elapsed6 << " seconds\n"; // ��ӡ�鲢����ĺ�ʱ
    std::cout << "\n";

    // ��v1�������򣬲���ʱ
    clock_t start7 = clock(); // ��ʼ��ʱ
    std::reverse(v1.begin(), v1.end()); // ����
    clock_t end7 = clock(); // ������ʱ
    double elapsed7 = (double)(end7 - start7) / CLOCKS_PER_SEC; // �����ʱ

    // ��v2�������򣬲���ʱ
    clock_t start8 = clock(); // ��ʼ��ʱ
    std::reverse(v2.begin(), v2.end()); // ����
    clock_t end8 = clock(); // ������ʱ
    double elapsed8 = (double)(end8 - start8) / CLOCKS_PER_SEC; // �����ʱ

    std::cout << "\n";

    // ��v1�����������򣬲���ʱ
    clock_t start9 = clock(); // ��ʼ��ʱ
    bubble_sort(v1, compare_complex); // ��������
    clock_t end9 = clock(); // ������ʱ
    double elapsed9 = (double)(end9 - start9) / CLOCKS_PER_SEC; // �����ʱ

    // ��v2���й鲢���򣬲���ʱ
    clock_t start10 = clock(); // ��ʼ��ʱ
    merge_sort(v2, 0, v2.size() - 1, compare_complex); // �鲢����
    clock_t end10 = clock(); // ������ʱ
    double elapsed10 = (double)(end10 - start10) / CLOCKS_PER_SEC; // �����ʱ

    // ��ӡ���
    std::cout << "�������������������ʱ: " << elapsed9 << " seconds\n"; // ��ӡ��������ĺ�ʱ
    std::cout << "���������Ĺ鲢�����ʱ: " << elapsed10 << " seconds\n"; // ��ӡ�鲢����ĺ�ʱ

    std::cout << "\n";

    // ����һ����СΪ1000�������������
    std::vector<Complex> v3 = generate_random_complex_vector(10);

    // ��ԭʼ�����������򣬵õ�˳������
    std::sort(v.begin(), v.end(), compare_complex);

    // ��ӡ˳������
    std::cout << "˳��������\n";
    print_vector(v);

    std::cout << "\n";

    // ��������ģ�����޺�����
    double m1 = 5.0;
    double m2 = 10.0;

    // ����������Һ������õ�������
    std::vector<Complex> sub_v = range_search(v, m1, m2);

    // ��ӡ������
    std::cout << "ģ����[" << m1 << ", " << m2 << ") �ĸ����У�\n";
    print_vector(sub_v);

    return 0;
}
