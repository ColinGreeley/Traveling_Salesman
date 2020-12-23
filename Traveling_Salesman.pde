
// Colin Greeley
// Traveling Salesman problem with genetic algorithm
// 2018 Crimson Code Hackathon
// 3/3/2018

import processing.opengl.*;


int cityCount = 50;
int populationSize = 50000;
float selectionRate = 0.3;
float crossoverRate = 0.3;
float mutationRate = 0.2;
float flipRate = 0.3;
float shiftRate = 0.2;
int regenerationRate = 500;
int restartRate = 50;


float[] x = new float[cityCount];
float[] y = new float[cityCount];
PVector[][] cities = new PVector[populationSize][cityCount];
PVector[][] newCities = new PVector[populationSize][cityCount];
PVector[] bestPath = new PVector[cityCount];
float[] pathSum = new float[populationSize];
PVector[] bestCumulativePath = new PVector[cityCount];
float bestPathMag = 1000000;
float bestCumulativePathMag = 1000000;
int shortestPathIndex;
int generation = 0;

Generate g;
Algorithm a;
Path p;


void setup() {
  size(1700, 900, OPENGL);
  //fullScreen();
  colorMode(HSB);

  g = new Generate();
  a = new Algorithm();
  p = new Path();

  g.Start();
  g.shufflePopulation();
}
 

void draw() {
  background(52);
  
   g.displayCities();
   p.calculatePathMagnitude();
   shortestPathIndex = p.bestPath();
   p.drawBestPath(0);
   
  if (keyPressed || generation % 10 != 0) {
    a.selection();
    a.crossover();
    a.mutate();
    a.flip();
    a.shift();
    a.nextGeneration();
  }
  a.showGeneration();
  p.overallBestPath(100);
  println(generation);
}
