/*
 *  sorts.h
 *
 *  Created on: 09/09/2023
 *  Author: Carlos Davalos 
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
class Sorts{
private:
	void swap(vector<T>& arreglo, int index1, int index2){
		T temp = arreglo[index2];
		arreglo[index2] = arreglo[index1];
		arreglo[index1] = temp;
	}

	void merge(vector<T>& arreglo, int start, int end){
		// Copiar arreglo
		vector<T> copia(arreglo);
		int index_1 = start;
		int index_2 = floor((start+end)/2) + 1;
		int index_copia = start;

		// Hacer el sort
		while ((index_1<=floor((start+end)/2)) && (index_2<=end)){
			if (arreglo[index_1] <= arreglo[index_2]){
				copia[index_copia] = arreglo[index_1];
				index_1++;
			} else{
				copia[index_copia] = arreglo[index_2];
				index_2++;
			}
			index_copia++;
		}

		// Copiar los elementos restantes
		while(index_1<=floor((start+end)/2)){
			copia[index_copia] = arreglo[index_1];
			index_1++;
			index_copia++;
		}
		while(index_2<=end){
			copia[index_copia] = arreglo[index_2];
			index_2++;
			index_copia++;
		}

		// Actualizar el arreglo originar
		for (int i=start; i<=end; i++){
			arreglo[i] = copia[i];
		}
	}

	void split(vector<T>& arreglo, int start, int end){
		if (start == end){
			return;
		}
		split(arreglo, start, floor((start+end)/2));
		split(arreglo, floor((start+end)/2)+1, end);
		merge(arreglo, start, end);
	}

	int busqBinaria(vector<T>& arreglo, int value, int start, int end){
		if (end-start > 0){
			int mitad = floor((start+end)/2);
			if (arreglo[mitad] == value){
				return mitad;
			} 
			if (value < arreglo[mitad]){
				return busqBinaria(arreglo, value, start, mitad);
			}
			return busqBinaria(arreglo, value, mitad+1, end);
		}
		return start;
	}

public:
	Sorts(){}

	void ordenaSeleccion(vector<T>& arreglo){
		for (int i=0; i<arreglo.size(); i++ ){
			int min_index = i;

			for (int j=i; j<arreglo.size(); j++ ){
				if (arreglo[j] < arreglo[min_index]){
					min_index = j;
				}
			}
			swap(arreglo, i, min_index);
		}
	}

	void ordenaBurbuja(vector<T>& arreglo){
		for (int i=1; i<arreglo.size(); i++){
			for (int j=0; j<arreglo.size()-i; j++){
				if (arreglo[j+1] < arreglo[j]){
					swap(arreglo, j+1, j);
				}
			}
		}
	}

	void ordenaMerge(vector<T>& arreglo){
		split(arreglo, 0, arreglo.size()-1);
	}

	int busqSecuencial(vector<T>& arreglo, int value){
		for (int i=0; i<arreglo.size(); i++){
			if (arreglo[i] == value){
				return i;
			}
		}
		return -1;
	}

	int busqBinaria(vector<T>& arreglo, int value){
		int i = busqBinaria(arreglo, value, 0, arreglo.size());
		return i;
	}
};