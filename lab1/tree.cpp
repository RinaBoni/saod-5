// BibDev зависит от класса ThreeNode
template <class T>
class BibDev;


template <class T> // ќбъ€вление объекта дл€ узла бинарного дерева
class ThreeNode {
private:
	// укзатели левого и правого дочерних узлов
	ThreeNode<T>* left;
	ThreeNode<T>* right;
public:

	T data; // открытый элемент, допускающий обновление


	ThreeNode(const T& data, ThreeNode<T>* L = nullptr, ThreeNode<T>* R = nullptr) { // конструктор
		this->data = data;
		this->left = L;
		this->right = R;
	}

	ThreeNode<T>* Right() const { // методы доступа к пол€м указателей
		return this->right;
	}

	ThreeNode<T>* Left() const {
		return this->left;
	}

	// сделать класс BibDev дружественным поскольку необходим доступ к пол€м
	friend class BibDev<T>;
};

