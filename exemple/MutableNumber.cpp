/**
 * \file MutableNumber.cpp
 * \brief Fichier de d'implémentation de la classe MutableNumber
 * \author Luc Doppler & Léo Sumi
 * \date 03/04/15
 */

#include "MutableNumber.hpp"

#include <cassert>

#include "../Random/Random.hpp" // pour bernoulli() et normal()

// Constructeur

MutableNumber::MutableNumber(double value, double probDeMut, double ecartType, bool aUneBorneInf, double borneInf, bool aUneBorneSup, double borneSup)
	: value_(value),
	probDeMut_(probDeMut),
	ecartType_(ecartType),
	aUneBorneInf_(aUneBorneInf),
	borneInf_(borneInf),
	aUneBorneSup_(aUneBorneSup),
	borneSup_(borneSup)
{
	controleDesBornes();
}

MutableNumber::MutableNumber(j::Value const& fichierConfig)
	: MutableNumber(
		fichierConfig["initial"].toDouble(),
		fichierConfig["rate"].toDouble(),
		fichierConfig["sigma"].toDouble()
		)
{
	controleDesBornes();
}

/*
MutableNumber::MutableNumber(j::Value const& fichierConfig)
	: value_(fichierConfig["initial"].toDouble()),
	probDeMut_(fichierConfig["rate"].toDouble()),
	ecartType_(fichierConfig["sigma"].toDouble()),
	aUneBorneInf_(fichierConfig["clamp min"].toBool()),
	borneInf_(fichierConfig["min"].toDouble()),
	aUneBorneSup_(fichierConfig["clamp max"].toBool()),
	borneSup_(fichierConfig["max"].toDouble())
{
	controleDesBornes();
}
*/

// Méthode de l'interface

double MutableNumber::get() const
{
	return value_;
}

void MutableNumber::set(double value)
{
	value_ = value;
	controleDesBornes();
}

void MutableNumber::mutate()
{
	// bernoulli retourne avec la probabilité probDeMut_ et 0 avec la probablité 1-probDeMut
	if (bernoulli(probDeMut_) == 1)
	{
		value_ += normal(0, ecartType_*ecartType_);
		controleDesBornes();
	}
}

// static

MutableNumber MutableNumber::probability(double initialValue, double mutationProbability, double sigma)
{
	MutableNumber probabilite(initialValue, mutationProbability, sigma, true, 0, true, 1);
	probabilite.controleDesBornes();
	return probabilite;
}

MutableNumber MutableNumber::probability(j::Value const& fichierConfig)
{
	MutableNumber probabilite(fichierConfig);

	// Contrôle des valeurs du fichier de configuration
	if (!probabilite.aUneBorneInf_)
	{
		probabilite.aUneBorneInf_ = true;
		probabilite.borneInf_ = 0;
	}
	else if (probabilite.borneInf_ != 0)
	{
		probabilite.borneInf_ = 0;
	}
	if (!probabilite.aUneBorneSup_)
	{
		probabilite.aUneBorneSup_ = true;
		probabilite.borneSup_ = 1;
	}
	else if (probabilite.borneSup_ != 1)
	{
		probabilite.borneSup_ = 1;
	}

	probabilite.controleDesBornes();

	return probabilite;
}

MutableNumber MutableNumber::positive(double initialValue, double mutationProbability, double sigma, bool hasMax, double max)
{
	MutableNumber positif(initialValue, mutationProbability, sigma, true, 0, hasMax, max);

	if (hasMax)
	{
		assert(max >= 0);
	}

	positif.controleDesBornes();

	return positif;
}

MutableNumber MutableNumber::positive(j::Value const& fichierConfig, bool hasMax, double max)
{
	MutableNumber positif(fichierConfig);

	// Contrôle des valeur du fichier de configuration
	if (!positif.aUneBorneInf_)
	{
		positif.aUneBorneInf_ = true;
		positif.borneInf_ = 0;
	}
	else if (positif.borneInf_ != 0)
	{
		positif.borneInf_ = 0;
	}

	if (hasMax)
	{
		assert(max >= 0);
	}

	positif.controleDesBornes();

	return positif;
}
		
// Méthode membre

void MutableNumber::controleDesBornes()
{
	if (aUneBorneInf_ and value_ < borneInf_)
	{
		value_ = borneInf_;
	}
	else if (aUneBorneSup_ and value_ > borneSup_)
	{
		value_ = borneSup_;
	}
}
