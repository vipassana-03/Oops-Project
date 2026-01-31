#pragma once
#include <string>
void setTimeScale(long long scale);
long long nowMs();
std::string formatTime(long long ms);
std::string normalizePlate(std::string plate); //used to normalize license plate input
bool isValidPlateFormat(const std::string& plate); //used to check whether or license plate inputs are valid.
std::string formatDuration(long long ms);
std::string jsonEscape(const std::string& input); // used to insure that stuff doesn't break when special characters are used
