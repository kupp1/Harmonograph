/*
 *   Copyright 2020-2021 Artem Bakin and Dmitriy Kuperstein
 *
 *   This file is part of Harmonograph.
 *
 *   Harmonograph is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Harmonograph is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Harmonograph.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "Pendulum.h"

std::vector<PendulumDimension*> Pendulum::getDimensionsCopy() {
	std::vector<PendulumDimension*> dimensionsCopy;

	for (PendulumDimension* d : dimensions) {
		dimensionsCopy.push_back(d->getDimensionCopy());
	}

	return dimensionsCopy;
}

float Pendulum::getCoordinateByTime(Dimension dimension, float t) {
	const int index = static_cast<std::underlying_type<Dimension>::type>(dimension);

	PendulumDimension* currentDimension = dimensions.at(index);

	if(index%2==0){
		return exp(-currentDimension->dumping * t) * cos(currentDimension->frequency * t + currentDimension->phase);
	}
	else{
		return exp(-currentDimension->dumping * t) * sin(currentDimension->frequency * t + currentDimension->phase);
	}

	
}
void Pendulum::update(float frequencyPoint, bool isCircle) {
	int r = rand();
	for (PendulumDimension* dimension : dimensions) {
		dimension->update(frequencyPoint, isCircle, r);
	}
}
void Pendulum::changeDimensionEquationPhase(Dimension dimension, float radians) {
	const int dimensionIndex = static_cast<std::underlying_type<Dimension>::type>(dimension);

	dimensions.at(dimensionIndex)->phase+=radians;
}
void Pendulum::updateFrequencyPoint(float frequencyPoint) {
	for (PendulumDimension* dimension : dimensions) {
		dimension->updateFrequencyPoint(frequencyPoint);
	}
}
float Pendulum::getEquationParameter(Dimension dimension, EquationParameter parameter) {
	const int index = static_cast<std::underlying_type<Dimension>::type>(dimension);

	switch (parameter){
	case EquationParameter::amplitude:
		return dimensions.at(index)->amplitude;
		break;
	case EquationParameter::dumping:
		return dimensions.at(index)->dumping;
		break;
	case EquationParameter::frequency:
		return dimensions.at(index)->frequency;
		break;
	case EquationParameter::phase:
		return dimensions.at(index)->phase;
		break;
	case EquationParameter::frequencyNoise:
		return dimensions.at(index)->frequencyNoise;
		break;
	default:
		return 0;
		break;
	}
}
void Pendulum::setEquationParameter(Dimension dimension, EquationParameter parameter, float value) {
	const int index = static_cast<std::underlying_type<Dimension>::type>(dimension);

	switch (parameter) {
	case EquationParameter::amplitude:
		dimensions.at(index)->amplitude = value;
		break;
	case EquationParameter::dumping:
		dimensions.at(index)->dumping = value;
		break;
	case EquationParameter::frequency:
		dimensions.at(index)->frequency = value;
		break;
	case EquationParameter::phase:
		dimensions.at(index)->phase = value;
		break;
	case EquationParameter::frequencyNoise:
		dimensions.at(index)->frequencyNoise = value;
		break;
	}
}
Pendulum::Pendulum(Pendulum* pendulum) {
	dimensions = pendulum->getDimensionsCopy();
}
Pendulum::Pendulum() {
	for (int i = 0; i < 3; i++) {
		dimensions.push_back(new PendulumDimension(2, false, 0));
	}
	this->update(2, false);
}

Pendulum::Pendulum(std::vector<PendulumDimension*> dimensions) {
	this->dimensions = dimensions;
}

Pendulum::Pendulum(int dimensionsCount, float frequencyPoint, bool isCircle) {
	const int r = rand();
	for (int i = 0; i < dimensionsCount; i++) {
		dimensions.push_back(new PendulumDimension(frequencyPoint, isCircle, r));
	}
	this->update(frequencyPoint, isCircle);
}
