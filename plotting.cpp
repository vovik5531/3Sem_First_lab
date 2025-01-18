#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "plotting.hpp"

std::pair<double, double> linearRegression(const std::vector<double>& x, const std::vector<double>& y) 
{
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Размеры векторов должны совпадать и быть больше нуля.");
    }

    double n = x.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (size_t i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;

    return {slope, intercept};
}
int xOffSet = 25; 
int yOffset = 540; 
void drawGraph(sf::RenderWindow& window, const std::vector<double>& x,
    const std::vector<double>& y, 
    double slope, double intercept, 
    const std::string& xAxisName, const std::string& yAxisName, 
    int xPositionOnCanvas=100, int yPositionOnCanvas = 200) 
{ 
    for (size_t i = 0; i < x.size(); ++i) {
        sf::CircleShape point(2);
        point.setPosition(x[i] + xPositionOnCanvas-2+xOffSet, yOffset+ yPositionOnCanvas - y[i] -2 );
        point.setFillColor(sf::Color::Blue);
        window.draw(point);
    }
    // sf::CircleShape centerPoint(4);
    // centerPoint.setPosition(xPositionOnCanvas+xOffSet, yOffset+ yPositionOnCanvas);
    // centerPoint.setFillColor(sf::Color::Red);
    // window.draw(centerPoint); 
    // double xMin = *min_element(x.begin(), x.end());
    // double xMax = *max_element(x.begin(), x.end());
    // sf::Vertex line[] = {
    //     sf::Vertex(sf::Vector2f(xMin * 50 + 100, 600 - (slope * xMin + intercept) * 50), sf::Color::Red),
    //     sf::Vertex(sf::Vector2f(xMax * 50 + 100, 600 - (slope * xMax + intercept) * 50), sf::Color::Red)
    // };
    // window.draw(line, 2, sf::Lines);
    sf::Font font;
    font.loadFromFile("./Eilaria Regular.ttf"); 
    if (!font.loadFromFile("./Eilaria Regular.ttf")) {
        std::cerr << "Error while loading font!" << std::endl;
        return;
    }

    sf::Text xAxisLabel(xAxisName, font, 20);
    xAxisLabel.setFillColor(sf::Color::Black);
    xAxisLabel.setPosition(40+xPositionOnCanvas+xOffSet, yOffset+15+yPositionOnCanvas);
    

    sf::Text firstPlotName("Graph of time dependence on the number of pointers of each type", font, 20);
    firstPlotName.setFillColor(sf::Color::Black);

    sf::Text yAxisLabel(yAxisName, font, 16);
    yAxisLabel.setFillColor(sf::Color::Black);
    yAxisLabel.setPosition(xPositionOnCanvas-35+xOffSet, yOffset/2+yPositionOnCanvas);
    yAxisLabel.setRotation(-90); 
    
     sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas - 2+xOffSet, yOffset+yPositionOnCanvas), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas + 220+xOffSet, yOffset+yPositionOnCanvas), sf::Color::Black)
    };

    sf::Vertex arrowUp[] =
    {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas + 220-7+xOffSet, yOffset+yPositionOnCanvas-7), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas + 220+xOffSet, yOffset+yPositionOnCanvas), sf::Color::Black)
    };
    sf::Vertex arrowDown[] =
    {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas + 220-7+xOffSet, yOffset+yPositionOnCanvas+7), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas + 220+xOffSet, yOffset+yPositionOnCanvas), sf::Color::Black)
    };

    window.draw(arrowUp, 2, sf::Lines);
    window.draw(arrowDown, 2, sf::Lines);
    window.draw(xAxis, 3, sf::Lines);
    window.draw(xAxisLabel);

    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas+xOffSet, yOffset+2+yPositionOnCanvas), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas+xOffSet, yPositionOnCanvas-155), sf::Color::Black)
    };

    sf::Vertex arrowLeft[] = {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas+xOffSet, yPositionOnCanvas-155), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas-7+xOffSet, yPositionOnCanvas-155+7), sf::Color::Black)
    };

    sf::Vertex arrowRight[] = {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas+xOffSet, yPositionOnCanvas-155), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas+7+xOffSet, yPositionOnCanvas-155+7), sf::Color::Black)
    };
    for (int k=1; k<20; k++)
    {
        sf::Vertex stepY[] = {
        sf::Vertex(sf::Vector2f(xPositionOnCanvas-2+xOffSet, yOffset+2+yPositionOnCanvas-k*35), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xPositionOnCanvas+2+xOffSet, yOffset+2+yPositionOnCanvas-k*35), sf::Color::Black)
        };
        window.draw(stepY, 2, sf::Lines);
        if(k>1 & k%2==0)
        {
            sf::Text markY(std::to_string(k*35), font, 10);
            markY.setFillColor(sf::Color::Black);
            markY.setPosition(xPositionOnCanvas-17+xOffSet, yOffset-6+yPositionOnCanvas-k*35);
            window.draw(markY); 
        }
    }
    for (int k=1; k<24; k++)
    {
       
        if(k%5==0)
        {
            sf::Vertex stepX[] = {
            sf::Vertex(sf::Vector2f(xPositionOnCanvas+10*k+xOffSet, yOffset+yPositionOnCanvas-2), sf::Color::Black),
            sf::Vertex(sf::Vector2f(xPositionOnCanvas+10*k+xOffSet, yOffset+2+yPositionOnCanvas+2), sf::Color::Black)
            };
            window.draw(stepX, 2, sf::Lines);
            sf::Text markX(std::to_string(k*10), font, 10);
            markX.setFillColor(sf::Color::Black);
            markX.setPosition(xPositionOnCanvas+10*k+xOffSet, yOffset+6+yPositionOnCanvas);
            window.draw(markX); 
        }
    }
    window.draw(arrowLeft, 2, sf::Lines);
    window.draw(arrowRight, 2, sf::Lines);
    window.draw(yAxis, 5, sf::Lines);
    window.draw(yAxisLabel);

    window.draw(firstPlotName);
    
}


void doPlotting() 
{
    int numPoints;
    std::vector<double> firstYValues =  generateArrayUniqPtr();
    std::vector<double> secondYValues = generateArraySharedPtr();  
    std::vector<double> thirdYValues = generateArrayStdSharedPtr(); 
    std::vector<double> forthYValues = generateArrayStdUnique_ptr(); 
    std::string xAxisName;
    std::vector<double> xValues;
    std::vector<double> yValues; 
    std::vector<double> deltaX;
    for(int i=0; i  < 200; i++)
    {
        xValues.push_back(i);
        deltaX.push_back(i);
        yValues.push_back(i); 
    }
    std::string xAxisNameFirstPlot = "UniquePtr(100'000)"; 
    std::string yAxisNameFirstPlot = "Time (miliseconds)";

    std::string xAxisNameSecondPlot = "SharedPtr(100'000)"; 
    std::string yAxisNameSecondPlot = "Time (miliseconds)";

    std::string xAxisNameThirdPlot = "std::shared_ptr(100'000)"; 
    std::string yAxisNameThirdPlot = "Time (miliseconds)";

    std::string xAxisNameForthPlot = "std::unique_ptr(100'000)"; 
    std::string yAxisNameForthPlot = "Time (miliseconds)";

    try {
        auto [slope, intercept] = linearRegression(xValues,yValues);
        sf::RenderWindow window(sf::VideoMode(1300, 800), "Time Testing");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::White);
            auto xSize = window.getSize().x;
            auto ySize = window.getSize().y;
            drawGraph(window, deltaX, firstYValues, slope, intercept, xAxisNameFirstPlot, yAxisNameFirstPlot, 30, ySize/4);
            drawGraph(window, deltaX, secondYValues, slope, intercept, xAxisNameSecondPlot, yAxisNameSecondPlot, 30+((xSize*1)/4), ySize/4);
            drawGraph(window, deltaX, thirdYValues, slope, intercept, xAxisNameThirdPlot, yAxisNameThirdPlot, 30+((xSize*2)/4), ySize/4);
            drawGraph(window, deltaX, forthYValues, slope, intercept, xAxisNameForthPlot, yAxisNameForthPlot, 30+((xSize*3)/4), ySize/4);
            window.display(); 
        }
    } 
    catch (const std::invalid_argument& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
