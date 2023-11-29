Estas actividades son para que practiques la implementación de algoritmos y estructuras de datos. **Estas actividades se basan en las actividades y programas desarrollados en clase, pero tienen pequeñas diferencias para garantizar que no copies y pegues el código ciegamente sin entenderlo**.

Cuando tengas que entregar la actividad en canvas por favor **solo entrega el archivo.h que lleva el nombre del algoritmo o estructura como se viene en el encabezado del main.**

Los cambios que puedes esperar son: 
el manejo de excepciones, 
los casos de prueba, 
los formatos de entrada y salida de algunas funciones.


	// Incluye estas funciones en tu dlist.h para poder imprimir tus respuestas
	// en formatos compatibles con el main

	template <class T>
	std::string DList<T>::toStringForward() const {
		std::stringstream aux;
		DLink<T> *p;

		p = head;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->next != 0) {
				aux << ", ";
			}
			p = p->next;
		}
		aux << "]";
		return aux.str();
	}

	template <class T>
	std::string DList<T>::toStringBackward() const {
		std::stringstream aux;
		DLink<T> *p;

		p = tail;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->previous != 0) {
				aux << ", ";
			}
			p = p->previous;
		}
		aux << "]";
		return aux.str();
	}
