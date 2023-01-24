// BibDev ������� �� ������ ThreeNode
template <class T>
class BibDev;


template <class T> // ���������� ������� ��� ���� ��������� ������
class ThreeNode {
private:
	// �������� ������ � ������� �������� �����
	ThreeNode<T>* left;
	ThreeNode<T>* right;
public:

	T data; // �������� �������, ����������� ����������


	ThreeNode(const T& data, ThreeNode<T>* L = nullptr, ThreeNode<T>* R = nullptr) { // �����������
		this->data = data;
		this->left = L;
		this->right = R;
	}

	ThreeNode<T>* Right() const { // ������ ������� � ����� ����������
		return this->right;
	}

	ThreeNode<T>* Left() const {
		return this->left;
	}

	// ������� ����� BibDev ������������� ��������� ��������� ������ � �����
	friend class BibDev<T>;
};

