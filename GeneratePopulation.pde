
class Generate {

  void Start() {

    for (int i = 0; i < cityCount; i++) {
      x[i] = random(100, 800);
      y[i] = random(200, 800);
    }

    for (int i = 0; i < populationSize; i++) {
      for (int j = 0; j < cityCount; j++) {
        cities[i][j] = new PVector();
        cities[i][j].set(x[j], y[j]);
      }
    }
  }


  void displayCities() {

    strokeWeight(5);
    stroke(0);
    fill(100);
    rect(90, 190, 720, 620, 20);

    strokeWeight(1);
    stroke(0);
    fill(255);

    for (int i = 0; i < cityCount; i++) {
      ellipse(cities[0][i].x, cities[0][i].y, 10, 10);
    }
  }


  void shufflePopulation() {

    float temp = 0;
    PVector tempCities = new PVector();
    float[] random = new float[cityCount];


    for (int k = 0; k < populationSize; k++) {
      for (int i = 0; i < cityCount; i++) {
        random[i] = random(0, 1);
      }
      for (int i = 0; i < cityCount - 1; i++) {
        for (int j = 0; j < cityCount - i - 1; j++) {
          if (random[j] > random[j+1]) {
            temp = random[j];
            tempCities = cities[k][j];
            random[j] = random[j+1];
            cities[k][j] = cities[k][j+1];
            random[j+1] = temp;
            cities[k][j+1] = tempCities;
          }
        }
      }
    }
  }


  void shuffleBestPath() {

    float temp = 0;
    PVector tempCities = new PVector();
    float[] random = new float[cityCount];

    if (bestCumulativePathMag < bestPathMag) {
      bestCumulativePathMag = bestPathMag;
      for (int i = 0; i < cityCount; i++) {
        bestCumulativePath[i] = bestPath[i];
      }
    }

    for (int i = 0; i < cityCount; i++) {
      //bestCumulativePath[i] = bestPath[i];
      random[i] = random(0, 1);
    }
    for (int i = 0; i < cityCount - 1; i++) {
      for (int j = 0; j < cityCount - i - 1; j++) {
        if (random[j] > random[j+1]) {
          temp = random[j];
          tempCities = bestPath[j];
          random[j] = random[j+1];
          bestPath[j] = bestPath[j+1];
          random[j+1] = temp;
          bestPath[j+1] = tempCities;
        }
      }
    }
  }
}