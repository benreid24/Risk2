#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include <map>
#include "Territory.hpp"

/**
 * Helper function to load XML file and return data in an easy to access format
 * Example key pair: "Risk2.Map.Data" -> "Resources/Data/map.csv"
 *
 * \param file The file to load from
 * \return A map with XML tag structure as the key and the data as values
 */
extern std::map<std::string,std::string> loadXML(std::string file);

/**
 * Helper function to load territory data from the csv file
 *
 * \param territoryVec A reference to a vector of Territory objects to populate
 * \param file The filename of the csv to load
 */
extern void loadTerritoryCSV(std::vector<Territory>& territoryVec, std::string file);

/**
 * Helper function to load continents from CSV
 *
 * \param conVec A reference to a vector of Continent objects to populate
 * \param file The file to load from
 */
extern void loadContinentCSV(std::vector<Continent>& conVec, std::string file);

/**
 * Helper function to convert a string to an int
 *
 * \param str The string to convert
 * \return The integer contained in the string
 */
int stringToInt(std::string str);

#endif // UTIL_HPP
