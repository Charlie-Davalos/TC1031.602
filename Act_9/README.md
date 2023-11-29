Estas actividades son para que practiques la implementación de algoritmos y estructuras de datos. **Estas actividades se basan en las actividades y programas desarrollados en clase, pero tienen pequeñas diferencias para garantizar que no copies y pegues el código ciegamente sin entenderlo**.

Cuando tengas que entregar la actividad en canvas por favor **solo entrega el archivo.h que lleva el nombre del algoritmo o estructura como se viene en el encabezado del main.**

Los cambios que puedes esperar son: 
el manejo de excepciones, 
los casos de prueba, 
los formatos de entrada y salida de algunas funciones.



    // impresion clase quadratic
    template <class Key, class Value>
    std::string Quadratic<Key, Value>::toString() const {
    	std::stringstream aux;
    	for (int i = 0; i < size; i++){
    			if (keys[i] != initialValue){
    				aux << "(" << i << " ";
    			  aux << keys[i] << " : " << values[i] << ") ";
    			}
    	}
    	return aux.str();
    }
