
class Algorithm {

  void selection() {

    float[] rand = new float[populationSize];

    for (int i = 0; i < populationSize; i++) {
      rand[i] = random(0, 1);
    }
   
    for (int i = 0; i < populationSize; i++) {
      if (rand[i] < selectionRate) {
        for (int j = 0; j < cityCount; j++) {
          if (bestPath[j] == null) {
            newCities[i][j] = cities[shortestPathIndex][j];
          } else {
            newCities[i][j] = bestPath[j];
          }
        }
      } else {
        for (int j = 0; j < cityCount; j++) {
          newCities[i][j] = cities[i][j];
        }
      }
    }
  }


  void crossover() {

    int start, end, index;
    float[] rand = new float[populationSize];

    for (int i = 0; i < populationSize; i++) {
      rand[i] = random(0, 1);
      if (rand[i] < crossoverRate) {
        start = (int)random(1, cityCount);
        end = (int)random(start + 1, cityCount);
        index = (int)random(1, populationSize);
        //println(start+"     "+end);
        for (int j = 0; j < cityCount; j++) {
          if (j < (end - start)) {
            newCities[i][j] = cities[index][j+start];
          } else if ((j > (end - start)-1) && (j < start + (end - start))) {
            newCities[i][j] = cities[index][j-(end-start)];
          } else {
            newCities[i][j] = cities[index][j];
          }
        }
      }
    }
  }


  void mutate() {

    float rand, index1, index2;
    PVector temp = new PVector();

    for (int i = 0; i < populationSize - 1; i++) {
      rand = random(0, 1);
      index1 = (int)random(cityCount - 1);
      index2 = (int)random(cityCount - 1);
      if (rand < mutationRate && i != shortestPathIndex) {
        temp = newCities[i][(int)index1];
        newCities[i][(int)index1] = newCities[i][(int)index2];
        newCities[i][(int)index2] = temp;
      }
    }
  }


  void flip() {

    int start, end;
    float[] rand = new float[populationSize];
    PVector temp = new PVector();

    for (int i = 0; i < populationSize; i++) {
      rand[i] = random(0, 1);
      if (rand[i] < flipRate) {
        start = (int)random(0, cityCount);
        end = (int)random(start + 1, cityCount);
        for (int j = 0; j < (end - start)/2; j++) {
          if (start < end) {
            temp = newCities[i][start];
            newCities[i][start] = newCities[i][end];
            newCities[i][end] = temp;
            start++;
            end--;
          }
        }
      }
    }
  }


  void shift() {

    int index1, index2;
    PVector temp = new PVector();
    float[] rand = new float[populationSize];

    for (int i = 0; i < populationSize; i++) {
      rand[i] = random(0, 1);
      index1 = (int)random(0, cityCount - 1);
      index2 = (int)random(index1 + 1, cityCount - 1);
      if (rand[i] < shiftRate) {
        for (int j = index1; j < index2; j++) {
          if (j == index1) {
            temp = newCities[i][j];
          }
          if (j == index2-1) {
            newCities[i][j] = temp;
          } else {
            newCities[i][j] = newCities[i][j+1];
          }
        }
      }
    }
  }
  
  void showGeneration() {
    text("Generation", 890, 80);
    text(generation, 1100, 80);
  }


  void nextGeneration() {

    for (int i = 0; i < populationSize; i++) {
      for (int j = 0; j < cityCount; j++) {
        cities[i][j] = newCities[i][j];
      }


        }
     
    if (generation % restartRate == 0) {
      g.shuffleBestPath();
    }

    generation++;
  }
}
