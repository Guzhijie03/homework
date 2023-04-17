using Rank = unsigned int; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
template <typename T> class Vector { //����ģ����
protected:
    Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
    void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)
    void expand(); //�ռ䲻��ʱ����
    void shrink(); //װ�����ӹ�Сʱѹ��
    bool bubble(Rank lo, Rank hi); //ɨ�轻��
    void bubbleSort(Rank lo, Rank hi); //���������㷨
    Rank maxItem(Rank lo, Rank hi); //ѡȡ���Ԫ��
    void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
    void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
    void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
    void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
    Rank partition(Rank lo, Rank hi); //��㹹���㷨
    void quickSort(Rank lo, Rank hi); //���������㷨
    void shellSort(Rank lo, Rank hi); //ϣ�������㷨
public:
    // ���캯��
    Vector(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
    // ��������
    ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�
    // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    Rank find(T const& e) const { return find(e, 0, _size); } //���������������
    Rank find(T const& e, Rank lo, Rank hi) const; //���������������
    Rank search(T const& e) const //���������������
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //���������������
    // ��д���ʽӿ�
    T& operator[] (Rank r); //�����±������������������������ʽ���ø�Ԫ��
    const T& operator[] (Rank r) const; //����������ֵ�����ذ汾
    Vector<T>& operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    T remove(Rank r); //ɾ����Ϊr��Ԫ��
    Rank remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    Rank insert(Rank r, T const& e); //����Ԫ��
    Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    void sort(Rank lo, Rank hi); //��[lo, hi)����
    void sort() { sort(0, _size); } //��������
    void unsort(Rank lo, Rank hi); //��[lo, hi)����
    void unsort() { unsort(0, _size); } //��������
    Rank deduplicate(); //����ȥ��
    Rank uniquify(); //����ȥ��
    // ����
    void traverse(void (*) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector

template < typename T> //TΪ�������ͣ��������ظ�ֵ������'='
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //����������A[lo, hi)Ϊ������������
    _elem = new T[_capacity = max<Rank>(DEFAULT_CAPACITY, 2 * (hi - lo))]; //����ռ�
    for (_size = 0; lo < hi; _size++, lo++) //A[lo, hi)�ڵ�Ԫ����һ
        _elem[_size] = A[lo]; //������_elem[0, hi - lo)
} //��const���Σ���֤A�е�Ԫ�ز��±��۸ģ�����ʱ�� = O(hi-lo)

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V) { //���
    if (_elem) delete[] _elem; //�ͷ�ԭ������
    copyFrom(V._elem, 0, V.size()); //���帴��
    return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template <typename T> void Vector<T>::expand() { //�����ռ䲻��ʱ����
    if (_size < _capacity) return; //��δ��Աʱ����������
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //��������С����
    T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
    for (Rank i = 0; i < _size; i++)
        _elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
    delete[] oldElem; //�ͷ�ԭ�ռ�
}

template <typename T> void Vector<T>::shrink() { //װ�����ӹ�Сʱѹ��������ռ�ռ�
    if (_capacity < DEFAULT_CAPACITY << 1) return; //����������DEFAULT_CAPACITY����
    if (_size << 2 > _capacity) return; //��25%Ϊ��
    T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //��������
    for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i]; //����ԭ��������
    delete[] oldElem; //�ͷ�ԭ�ռ�
}

template <typename T> T& Vector<T>::operator[] (Rank r) //�����±������
{
    return _elem[r];
} // assert: 0 <= r < _size
template <typename T> const T& Vector<T>::operator[] (Rank r) const //����������ֵ
{
    return _elem[r];
} // assert: 0 <= r < _size

template <typename T> void permute(Vector<T>& V) { //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
    for (int i = V.size(); i > 0; i--) //�Ժ���ǰ
        swap(V[i - 1], V[rand() % i]); //V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //�����������[lo, hi)
    T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
    for (Rank i = hi - lo; 1 < i; --i) //�Ժ���ǰ
        swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������
}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } // less than
template <typename T> static bool lt(T& a, T& b) { return a < b; } // less than
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } // equal
template <typename T> static bool eq(T& a, T& b) { return a == b; } // equal

template < typename T> //������������˳�����e���ɹ��򷵻����ĳ���λ�ã����򷵻�lo-1
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const { //0 <= lo < hi <= _size
    while ((lo < hi--) && (e != _elem[hi])); //�Ӻ���ǰ��˳�����
    return hi; //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}

template < typename T> //��e������[r]
Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
    expand(); //���Ҫ��������
    for (Rank i = _size; r < i; i--) //�Ժ���ǰ�����Ԫ��
        _elem[i] = _elem[i - 1]; //˳�κ���һ����Ԫ
    _elem[r] = e; _size++; //������Ԫ�ز���������
    return r; //������
}

template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
    if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����
    while (hi < _size) _elem[lo++] = _elem[hi++]; //��׺[hi, _size)˳��ǰ��hi-loλ
    _size = lo; shrink(); //���¹�ģ��lo=_size֮��������������㣻���Ҫ��������
    //���б�Ҫ��������
    return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}

template <typename T> T Vector<T>::remove(Rank r) { //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
    T e = _elem[r]; //���ݱ�ɾ��Ԫ��
    remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
    return e; //���ر�ɾ��Ԫ��
}

template <typename T> Rank Vector<T>::deduplicate() { //ɾ�������������ظ�Ԫ�أ���Ч�棩
    Rank oldSize = _size; //��¼ԭ��ģ
    for (Rank i = 1; i < _size; ) //��ǰ����������_elem[1,_size)
        if (-1 == find(_elem[i], 0, i)) //��ǰ׺[0,i)��Ѱ����[i]��ͬ�ߣ�����һ������O(i)
            i++; //������ͬ���������������
        else
            remove(i); //����ɾ��[i]��O(_size-i)
    return oldSize - _size; //��ɾ��Ԫ������
}

template <typename T> void Vector<T>::traverse(void (*visit)(T&)) //��������ָ�����
{
    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
} //��������
template <typename T> template < typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���������������
{
    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
} //��������

template <typename T> struct Increase //�������󣺵���һ��T�����
{
    virtual void operator()(T& e) { e++; }
}; //����T��ֱ�ӵ�����������++

template <typename T> void increase(Vector<T>& V) //ͳһ���������еĸ�Ԫ��
{
    V.traverse(Increase<T>());
} //��Increase<T>()Ϊ�����������б���

template <typename T> Rank Vector<T>::uniquify() { //���������ظ�Ԫ���޳��㷨����Ч�棩
    Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
    while (++j < _size) //��һɨ�裬ֱ��ĩԪ��
        if (_elem[i] != _elem[j]) //������ͬ��
            _elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
    _size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
    return j - i; //������ģ�仯��������ɾ��Ԫ������
}

template < typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const { // 0 <= lo < hi <= _size
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
} //�ȸ��ʵ����ʹ�ö��ֲ��ҡ�Fibonacci����

//���ֲ����㷨���汾A��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T> static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
    while (lo < hi) { //ÿ����������Ҫ�����αȽ��жϣ���������֧
        Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�������۰룬��Ч������ֵ��ʾ������һλ��
        if (e < S[mi]) hi = mi; //����ǰ���[lo, mi)��������
        else if (S[mi] < e) lo = mi + 1; //�������(mi, hi)��������
        else                 \
            return mi; //��mi������
    } //�ɹ����ҿ�����ǰ��ֹ
    return -1; //����ʧ��
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��

