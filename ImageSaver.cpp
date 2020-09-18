#include "ImageSaver.h"

ImageSaver::ImageSaver() {
	//load settings logic
}

void ImageSaver::saveImage(QString filename, QImage image) {
	image.save(filename);
}

void ImageSaver::saveParametersToFile(QString filename, Harmonograph* harmonograph) {
	json j;
	j["numOfPendulums"] = harmonograph->getNumOfPendulums();
	j["frequencyRatio"] = std::to_string(harmonograph->firstRatioValue) + ":" + std::to_string(harmonograph->secondRatioValue);
	j["frequencyPoint"] = harmonograph->frequencyPoint;
	j["isStar"] = harmonograph->isStar;
	j["isCircle"] = harmonograph->isCircle;

	std::vector<Pendulum*> pendlms = harmonograph->getPundlumsCopy();

	for (int i = 0; i < pendlms.size(); i++) {
		j["pendulums"][i]["xDamp"] = pendlms.at(i)->xDumping;
		j["pendulums"][i]["xPhase"] = pendlms.at(i)->xPhase;
		j["pendulums"][i]["xFreq"] = pendlms.at(i)->xFreq;
		j["pendulums"][i]["xAmpl"] = pendlms.at(i)->xAmplitude;
		j["pendulums"][i]["yDamp"] = pendlms.at(i)->yDumping;
		j["pendulums"][i]["yPhase"] = pendlms.at(i)->yPhase;
		j["pendulums"][i]["yFreq"] = pendlms.at(i)->yFreq;
		j["pendulums"][i]["yAmpl"] = pendlms.at(i)->yAmplitude;

	}

	std::ofstream file(filename.toStdString());
	file << j.dump(4);
	file.close();

	delete harmonograph;
}

Harmonograph* ImageSaver::loadParametersFromFile(QString filename) {
	if (!filename.isEmpty()) {
		try {
			std::ifstream file(filename.toStdString());

			json j = json::parse(file);
			int numOfPendulums = j["numOfPendulums"];
			std::string ratio = j["frequencyRatio"];
			int firstRatioValue = std::stoi(ratio.substr(0, ratio.find(':')));
			int secondRatioValue = std::stoi(ratio.substr(ratio.find(':')+1, ratio.size()-1));
			float frequencyPoint = j["frequencyPoint"];
			bool isStar = j["isStar"];
			bool isCircle = j["isCircle"];

			std::vector<Pendulum*> pendulums;

			for (int i = 0; i < numOfPendulums; i++) {
				Pendulum* pendulum = new Pendulum(j["pendulums"][i]["xDamp"],
					j["pendulums"][i]["xPhase"], 
					j["pendulums"][i]["xFreq"], 
					j["pendulums"][i]["xAmpl"],
					j["pendulums"][i]["yDamp"], 
					j["pendulums"][i]["yPhase"],
					j["pendulums"][i]["yFreq"],
					j["pendulums"][i]["yAmpl"]);		

				pendulums.push_back(pendulum);
			}

			Harmonograph* harmonograph = new Harmonograph(pendulums, firstRatioValue, secondRatioValue, isStar, isCircle, frequencyPoint);
			return harmonograph;
		}
		catch (...) {
			return nullptr;
			//file.close();
		}

	}
	return nullptr;
}