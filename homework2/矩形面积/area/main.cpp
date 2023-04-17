#include <iostream>
#include <vector>
#include <random>

// ������һ���Ƚ��ȳ���FIFO�������ݽṹ�������������������ʵ��
// ����������������ʵ��һ���򵥵Ķ�����
class Queue {
private:
    std::vector<int> data; // ��һ�� vector ���洢�����е�Ԫ��
    int front; // ����Ԫ�ص��±�
    int rear; // ��βԪ�ص���һ���±�
    int size; // ������Ԫ�صĸ���
    int capacity; // ���е�����

public:
    // ���캯������ʼ������
    Queue(int cap) {
        data.resize(cap); // ����ռ�
        front = 0; // �����±�Ϊ 0
        rear = 0; // ��β�±�Ϊ 0
        size = 0; // ����Ϊ��
        capacity = cap; // ��¼����
    }

    // �ж϶����Ƿ�Ϊ��
    bool isEmpty() {
        return size == 0;
    }

    // �ж϶����Ƿ�����
    bool isFull() {
        return size == capacity;
    }

    // ��Ӳ�������Ԫ�ؼ����β
    void enqueue(int x) {
        if (isFull()) { // ��������������׳��쳣
            throw std::runtime_error("Queue is full");
        }
        data[rear] = x; // ��Ԫ�ش����βλ��
        rear = (rear + 1) % capacity; // ���¶�β�±꣬�����������ĩβ��ѭ�������鿪ͷ
        size++; // ���¶��д�С
    }

    // ���Ӳ�����������Ԫ���Ƴ�������
    int dequeue() {
        if (isEmpty()) { // �������Ϊ�գ��׳��쳣
            throw std::runtime_error("Queue is empty");
        }
        int x = data[front]; // ȡ������Ԫ��
        front = (front + 1) % capacity; // ���¶����±꣬�����������ĩβ��ѭ�������鿪ͷ
        size--; // ���¶��д�С
        return x; // ���ض���Ԫ��
    }

    // ��ȡ����Ԫ�أ������Ƴ�
    int peek() {
        if (isEmpty()) { // �������Ϊ�գ��׳��쳣
            throw std::runtime_error("Queue is empty");
        }
        return data[front]; // ���ض���Ԫ��
    }
};

// ��2��ʵ�ּ�������������ĺ���������߶����飬��������
// ˼·��ʹ�õ�������ջ��ջ�д洢�߶�������±꣩�������߶����飬����ÿ���߶ȣ�
// ���ջΪ�ջ��ߵ�ǰ�߶ȴ��ڵ���ջ���߶ȣ��򽫵�ǰ�±���ջ��
// ����˵����ǰ�߶�С��ջ���߶ȣ���ô�Ϳ��Լ�����ջ���߶�Ϊ�ߵľ��������
// ���Ϊ��ǰ�±��ȥջ����һ���±��ټ�һ�����ջΪ�գ���Ϊ��ǰ�±꣩��
// ������������Ȼ��ջ���±��ջ���ظ�������̣�ֱ��ջΪ�ջ��ߵ�ǰ�߶ȴ��ڵ���ջ���߶�Ϊֹ��
// ������߶���������ջ��Ϊ�գ�˵������һЩ�߶�û�м����������ô�Ͱ���ͬ���ķ�����
// �����鳤��Ϊ��ǰ�±꣬������ջ���߶�Ϊ�ߵľ��������������������Ȼ��ջ���±��ջ��ֱ��ջΪ��Ϊֹ��
// �������������ɡ�
int largestRectangleArea(std::vector<int>& heights) {
    int n = heights.size(); // ��ȡ�߶�����ĳ���
    int maxArea = 0; // ��ʼ��������Ϊ 0
    Queue stack(n); // ����һ��������Ϊ��������ջ
    for (int i = 0; i < n; i++) { // �����߶�����
        while (!stack.isEmpty() && heights[i] < heights[stack.peek()]) { // ���ջ��Ϊ���ҵ�ǰ�߶�С��ջ���߶�
            int h = heights[stack.dequeue()]; // ȡ��ջ���߶�
            int w = stack.isEmpty() ? i : i - stack.peek() - 1; // ������
            maxArea = std::max(maxArea, h * w); // ����������
        }
        stack.enqueue(i); // ����ǰ�±���ջ
    }
    while (!stack.isEmpty()) { // ���ջ��Ϊ��
        int h = heights[stack.dequeue()]; // ȡ��ջ���߶�
        int w = stack.isEmpty() ? n : n - stack.peek() - 1; // ������
        maxArea = std::max(maxArea, h * w); // ����������
    }
    return maxArea; // ����������
}

// ��3��������� 10 �����ݽ��в��ԣ�1 <= heights.length <=105��0 <= heights[i] <= 104��
// ʹ�� C++ ��׼���е� random �������������
std::random_device rd; // ������豸
std::mt19937 gen(rd()); // �����������
std::uniform_int_distribution<> dis1(1, 105); // ���ȷֲ� [1, 105]
std::uniform_int_distribution<> dis2(0, 104); // ���ȷֲ� [0, 104]


int main()
{
    for (int i = 0; i < 10; i++) { // ѭ�� 10 ��
        int len = dis1(gen); // ������ɸ߶�����ĳ���
        std::vector<int> heights(len); // ����һ������Ϊ len �� vector
        for (int j = 0; j < len; j++) { // ���� vector
            heights[j] = dis2(gen); // �������ÿ��Ԫ�ص�ֵ
        }
        std::cout << "���� " << i + 1 << ": " << std::endl; // ��������������
        std::cout << "Heights: "; // ����߶�����
        for (int h : heights) {
            std::cout << h << " ";
        }
        std::cout << std::endl;
        std::cout << "������: " << largestRectangleArea(heights) << std::endl; // ������������
    }
    return 0;
}