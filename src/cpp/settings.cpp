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

#pragma once
#include "settings.h"

ColorTemplate::ColorTemplate(QColor primary, QColor secondary, QColor background) {
	primaryColor = primary;
	secondaryColor = secondary;
	backgroundColor = background;
}

NamedColorTemplate::NamedColorTemplate(long long id, QString filename, QString name, ColorTemplate colorTemplate) {
	this->id = id;
	this->filename = filename;
	this->name = name;
	this->colorTemplate = colorTemplate;
}
