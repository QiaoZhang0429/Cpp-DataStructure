/*
 * Movie.cpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 */
 
#include "Movie.hpp"

Movie::Movie(std::string n, int y){
	name = n;
	year = y;
	weight = 1 + (2015 - year);
}

Movie::~Movie(){
	;
}