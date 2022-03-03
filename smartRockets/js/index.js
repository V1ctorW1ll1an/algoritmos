var population;
var lifeSpan = 200;
var lifeP;
var count = 0;
var target;

function setup() {
    createCanvas(400, 300);
    rocket = new Rocket();
    population = new Population();
    lifeP = createP();
    target = createVector(width / 2, 50);
}

function draw() {
    background(0);
    population.run();
    lifeP.html(count);
    count++;
    if (count == lifeSpan) {
        // population = new Population();
        population.evaluate();
        population.selection();
        count = 0;
    }

    ellipse(target.x, target.y, 16, 16);
}

function Population() {
    this.rockets = [];
    this.populationSize = 25;
    this.matingPool = [];

    // criando uma população
    for (let index = 0; index < this.populationSize; index++) {
        this.rockets[index] = new Rocket();
    }

    this.evaluate = () => {
        var maxFit = 0;
        for (let i = 0; i < this.populationSize; i++) {
            this.rockets[i].calcFitness();
            if (this.rockets[i].fitness > maxFit) {
                maxFit = this.rockets[i].fitness;
            }
        }

        for (let i = 0; i < this.populationSize; i++) {
            this.rockets[i].fitness /= maxFit;
        }

        this.matingPool = [];

        for (let i = 0; i < this.populationSize; i++) {
            var n = this.rockets[i].fitness * 100;
            for (let j = 0; j < n; j++) {
                this.matingPool.push(this.rockets[i]);
            }
        }
    };

    this.selection = () => {
        var newRockets = [];
        for (let i = 0; i < this.rockets.length; i++) {
            var parentA = random(this.matingPool).dna;
            var parentB = random(this.matingPool).dna;
            var childDna = parentA.crossover(parentB);
            newRockets[i] = new Rocket(childDna);
        }

        this.rockets = newRockets;
    };

    this.run = () => {
        for (let i = 0; i < this.populationSize; i++) {
            this.rockets[i].update();
            this.rockets[i].show();
        }
    };
}

// criando DNA
function DNA(genes) {
    if (genes) {
        this.genes = genes;
    } else {
        this.genes = [];
        for (let index = 0; index < lifeSpan; index++) {
            this.genes[index] = p5.Vector.random2D();
            this.genes[index].setMag(0.1);
        }
    }
    this.crossover = (partner) => {
        var newGenes = [];
        var mid = floor(random(this.genes.length));
        for (let i = 0; i < this.genes.length; i++) {
            if (i > mid) {
                newGenes[i] = this.genes[i];
            } else {
                newGenes[i] = partner.genes[i];
            }
        }
        return new DNA(newGenes);
    };
}

function Rocket(dna) {
    this.position = createVector(width / 2, height);
    this.velocity = createVector();
    this.acceleration = createVector();

    if (dna) {
        this.dna = dna;
    } else {
        this.dna = new DNA();
    }
    this.fitness = 0;

    this.calcFitness = () => {
        var distanceRocketToTarget = dist(
            this.position.x,
            this.position.y,
            target.x,
            target.y
        );

        this.fitness = map(distanceRocketToTarget, 0, width, width, 0);
    };

    this.applyForce = (force) => {
        this.acceleration.add(force);
    };

    this.update = () => {
        this.applyForce(this.dna.genes[count]);
        this.velocity.add(this.acceleration);
        this.position.add(this.velocity);
        this.acceleration.mult(0);
    };

    this.show = () => {
        push();
        noStroke();
        fill(255, 150);
        translate(this.position.x, this.position.y);
        rotate(this.velocity.heading());
        rectMode(CENTER);
        rect(0, 0, 25, 5);
        pop();
    };
}
