/*
 * Movie.hpp
 * Author: Qiao Zhang
 * Date: 03/06/2016
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Edge.hpp"

class Movie{ 

public:

  std::string name;
  int year;
  int weight;
  std::vector<Node*> crew;

  /* constructor */
  Movie(std::string n, int y);

  /* deconstructor */
  ~Movie();

  /* overwrite less than operator to change max heap into min heap*/
  bool operator<(const Movie& other){
    return year > other.year;
  }
  
};

/* class used for comparing elements within a priority queue*/
class MoviePtrLess{
public:
  bool operator()(Movie* const & lhs, Movie* const & rhs) const{
    return *lhs < *rhs;
  }
};

#endif // MOVIE_HPP