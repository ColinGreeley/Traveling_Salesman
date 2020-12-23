
class Path {

  void calculatePathMagnitude() {

    for (int i = 0; i < populationSize; i++) {
      pathSum[i] = sqrt(pow(cities[i][0].x - cities[i][cityCount-1].x, 2) + pow(cities[i][0].y - cities[i][cityCount-1].y, 2));
    }
    for (int i = 0; i < populationSize; i++) {
      for (int j = 0; j < cityCount - 1; j++) {
        pathSum[i] += sqrt(pow(cities[i][j+1].x - cities[i][j].x, 2) + pow(cities[i][j+1].y - cities[i][j].y, 2));
      }
    }
    //println(sum);
  }


  int bestPath() {

    int index = 0;
    for (int i = 0; i < populationSize; i++) {
      if (pathSum[i] < bestPathMag) {
        index = i;
      }
    }
    return index;
  }


  void drawBestPath(int n) {

    stroke(n, 255, 255);
    strokeWeight(3);
    fill(255);
    textSize(30);
    text("Best path for current generation", 90, 100);
    text(pathSum[shortestPathIndex], 90, 150);
    text("(distance in pixles)", 350, 150);

    line(cities[shortestPathIndex][0].x, cities[shortestPathIndex][0].y, cities[shortestPathIndex][cityCount-1].x, cities[shortestPathIndex][cityCount-1].y);
    for (int i = 0; i < cityCount - 1; i++) {
      line(cities[shortestPathIndex][i+1].x, cities[shortestPathIndex][i+1].y, cities[shortestPathIndex][i].x, cities[shortestPathIndex][i].y);
    }
  }


  void overallBestPath(int n) {
    
    translate(800, 0);
    
    strokeWeight(5);
    stroke(0);
    fill(100);
    rect(90, 190, 720, 620, 20);
    
    fill(255);
    textSize(30);
    text("Overall best path:", 90, 130);
    text(bestPathMag, 350, 130);
    text("pixels", 530, 130);

    for (int i = 0; i < populationSize; i++) {
      if (pathSum[i] < bestPathMag) {
        bestPathMag = pathSum[i];
        for (int j = 0; j < cityCount; j++) {
          bestPath[j] = cities[i][j];
        }
      }
    }

    bestPathMag = sqrt(pow(bestPath[0].x - bestPath[cityCount-1].x, 2) + pow(bestPath[0].y - bestPath[cityCount-1].y, 2));
    for (int i = 0; i < cityCount - 1; i++) {
      bestPathMag += sqrt(pow(bestPath[i+1].x - bestPath[i].x, 2) + pow(bestPath[i+1].y - bestPath[i].y, 2));
    }
    stroke(0);
    strokeWeight(1);

    for (int i = 0; i < cityCount; i++) {
      ellipse(cities[0][i].x, cities[0][i].y, 10, 10);
    }

    stroke(n, 255, 255);
    strokeWeight(3);

    line(bestPath[0].x, bestPath[0].y, bestPath[cityCount-1].x, bestPath[cityCount-1].y);
    for (int i = 0; i < cityCount - 1; i++) {
      line(bestPath[i+1].x, bestPath[i+1].y, bestPath[i].x, bestPath[i].y);
    }

    translate(-800, 0);
  }
}
