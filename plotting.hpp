#ifndef PLOTTING_H
#define PLOTTING_H
#include <SFML/Graphics.hpp>
#include "timeTests.hpp"

void doPlotting();

void drawGraph(sf::RenderWindow& window, const std::vector<long long>& x, 
    const std::vector<long long>& y,
    double slope, double intercept, const std::string& xAxisName,
    const std::string& yAxisName, 
    int xPositionOnCanvas, int yPostionOnCanvas
    );

std::pair<double, double> linearRegression(const std::vector<double>& x, const std::vector<double>& y);

void drawAxesAndPoints(sf::RenderWindow& window, const std::vector<long long>& xValues, 
        const std::vector<long long>& yValues1, const std::vector<long long>& yValues2, 
        const std::string& legend1, const std::string& legend2, 
        int xPositionOnCanvas = 100, int yPositionOnCanvas = 400);

void testDrawing();
#endif /* PLOTTING_H */