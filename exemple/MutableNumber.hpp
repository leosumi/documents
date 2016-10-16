/**
 * \file MutableNumber.hpp
 * \brief Fichier de déclaration de la classe MutableNumber
 * \author Luc Doppler & Léo Sumi
 * \date 03/04/15
 */

#ifndef MUTABLENUMBER_HPP
#define MUTABLENUMBER_HPP

#include "../JSON/JSON.hpp"

/**
 * \class MutableNumber
 * \brief Classe représentant un nombre qui peut changer aléatoirement de valeur
 *
 * Le nombre aléatoire est un double
 * Utilise une distribution normale de moyenne nulle et d'écart type donné
 *
 */
class MutableNumber
{
public:

//Constructeur et Destructeur

	/**
 	 * \brief Constructeur
 	 */
	MutableNumber(double value, double probDeMut, double ecartType, bool aUneBorneInf = false, double borneInf = 0, bool aUneBorneSup = false, double borneSup = 0);
	MutableNumber(j::Value const& fichierConfig);
	MutableNumber() = default;

//Méthode de l'interface

	/**
 	 * \brief getter pour le nombre aléatoire
 	 *
	 *
 	 * \return La valeur de value_
 	 */
	double get() const;

	/**
	 * \brief setter pour le nombre aléatoire
	 *
	 * La méthode effectue un contrôle des bornes avec la méthode controleDesBornes()
	 *
	 * \param value : valeur de value_
	 */
	void set(double value);

	/**
	 * \brief Méthode qui permet de changer la valeur du nombre de façon aléatoire
	 *
	 * La méthode effectue un contrôle des bornes avec la méthode controleDesBornes()
	 *
	 */
	void mutate();

// Méthodes statiques

	/**
	 * \brief Méthodes retournant une probabilité
	 *
	 * Une probabilité est un MutableNumber entre 0 et 1
	 * Contrôle la cohérence des données fournient en paramètre
	 * Utilisation : a = MutableNumber::probability(...);
	 *
	 * \return un MutableNumber entre 0 et 1
	 */
	static MutableNumber probability(double initialValue, double mutationProbability, double sigma);
	static MutableNumber probability(j::Value const& fichierConfig);

	/**
	 * \brief fonction retournant un nombre positif
	 *
	 * Controle la cohérence des données fournient en paramètre
	 * Utilisation : a = MutableNumber::positive(...);
	 *
	 * \return un MutableNumber positif
	 */
	static MutableNumber positive(double initialValue, double mutationProbability, double sigma, bool hasMax = false, double max = 0);
	static MutableNumber positive(j::Value const& fichierConfig, bool hasMax = false, double max = 0);
	
private:

//Méthode membre

	/**
	 * \brief Affecte la valeur de la borne inférieure ou supérieure si celles-ci sont dépassées.
	 */
	void controleDesBornes();

//Attribut

	double value_;
	double probDeMut_; //probabilité de mutation
	double ecartType_;
	bool aUneBorneInf_;
	double borneInf_; //significatif que si aUneBorneInf = true
	bool aUneBorneSup_;
	double borneSup_; //significatif que si aUneBorneSup = true

};

#endif // MUTABLENUMBER_HPP
