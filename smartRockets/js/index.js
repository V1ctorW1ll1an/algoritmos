var population;
var lifeSpan = 200;
var lifeP;
var generations;
var generationsCount = 1;
var count = 0;
var target;
var maxForce = 0.2;

// rectangle
var rx = 100;
var ry = 150;
var rw = 200;
var rh = 10;

function setup() {
    createCanvas(400, 300);
    rocket = new Rocket();
    population = new Population();
    lifeP = createP();
    generations = createP();
    target = createVector(width / 2, 50);
}

function draw() {
    background(0);
    population.run();
    lifeP.html(count);
    generations.html(`Geração: ${generationsCount}`);
    count++;
    if (count == lifeSpan) {
        // population = new Population();
        population.evaluate();
        population.selection();
        count = 0;
        generationsCount++;
    }

    fill(255);
    rect(rx, ry, rw, rh);

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
            childDna.mutation();
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
            this.genes[index].setMag(maxForce);
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

    this.mutation = () => {
        for (let i = 0; i < this.genes.length; i++) {
            if (random(1) < 0.01) {
                this.genes[i] = p5.Vector.random2D();
                this.genes[i].setMag(maxForce);
            }
        }
    };
}

function Rocket(dna) {
    this.position = createVector(width / 2, height);
    this.velocity = createVector();
    this.acceleration = createVector();
    this.completed = false;
    this.crashed = false;

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
        if (this.completed) {
            this.fitness *= 10;
        }
        if (this.crashed) {
            this.fitness /= 10;
        }
    };

    this.applyForce = (force) => {
        this.acceleration.add(force);
    };

    this.update = () => {
        var d = dist(this.position.x, this.position.y, target.x, target.y);
        if (d < 10) {
            this.completed = true;
            this.position = target.copy();
        }

        if (
            this.position.x > rx &&
            this.position.x < rx + rw &&
            this.position.y > ry &&
            this.position.y < ry + rh
        ) {
            this.crashed = true;
        }
        if (this.position.x > width || this.position.x < 0) {
            this.crashed = true;
        }
        if (this.position.y > height || this.position.y < 0) {
            this.crashed = true;
        }
        this.applyForce(this.dna.genes[count]);
        if (!this.completed && !this.crashed) {
            this.velocity.add(this.acceleration);
            this.position.add(this.velocity);
            this.acceleration.mult(0);
            this.velocity.limit(4);
        }
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
