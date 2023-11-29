Estas actividades son para que practiques la implementación de algoritmos y estructuras de datos. **Estas actividades se basan en las actividades y programas desarrollados en clase, pero tienen pequeñas diferencias para garantizar que no copies y pegues el código ciegamente sin entenderlo**.

Cuando tengas que entregar la actividad en canvas por favor **solo entrega el archivo.h que lleva el nombre del algoritmo o estructura como se viene en el encabezado del main.**

Los cambios que puedes esperar son: 
el manejo de excepciones, 
los casos de prueba, 
los formatos de entrada y salida de algunas funciones.


Aqui hay algunas funciones que te puedes ayudar a desplegar tus resulados

	template <class T>
	void Node<T>::print_tree(std::stringstream &aux) const {
		if (parent != 0){
			aux << "\n node " << value;
			aux << " parent " << parent->value;
		}else
			aux << "\n root " << value;
		if (left != 0)
			aux << " left " << left->value;
		if (right != 0)
			aux << " right " << right->value;
		aux << "\n";
	
		if (left != 0) {
			left->print_tree(aux);
		}
		if (right != 0) {
			right->print_tree(aux);
		}
	}
	
	template <class T>
	void Node<T>::preorder(std::stringstream &aux) const {
		aux << value;
		if (left != 0) {
			aux << " ";
			left->preorder(aux);
		}
		if (right != 0) {
			aux << " ";
			right->preorder(aux);
		}
	}
	
	template <class T>
	void Node<T>::inorder(std::stringstream &aux) const {
		if (left != 0) {
			left->inorder(aux);
		}
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << value;
		if (right != 0) {
			right->inorder(aux);
		}
	}
	
	template <class T>
	void Node<T>::preorder(std::stringstream &aux) const {
		aux << value;
		if (left != 0) {
			aux << " ";
			left->preorder(aux);
		}
		if (right != 0) {
			aux << " ";
			right->preorder(aux);
		}
	}
