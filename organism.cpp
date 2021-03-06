#include "organism.hpp"
#include "consts.hpp"

Organism::Organism(int code[nTraits]):
	m_x(0),
	m_y(0),
	m_maxEnergy(100),
	m_energy(90)
{
	// Setting m_code equal to code
	m_code[nTraits];

	for(int i = 0; i < nTraits; i++) {
		m_code[i] = code[i];
	}

	m_health = 10*m_code[bodySize];
	m_combat = 3*m_code[stomachType];
}

Organism::Organism()
{
	// Setting m_code equal to code
	m_code[nTraits];

	for(int i = 0; i < nTraits; i++)
	{
		m_code[i] = 0;
	}

	m_health = 10*m_code[bodySize];
	m_combat = 3*m_code[stomachType];
}

Organism::~Organism()
{
	for(auto i = orders.begin(); i < orders.end(); i++)
	{
		delete(*i);
	} 
}

Organism Organism::repopulate(Organism &org1, Organism &org2)
{
	int newCode[nTraits];

	for(int i = 0; i < nTraits; i++)
	{
		int delta = abs(org1.getCode()[i] - org2.getCode()[i]);
		newCode[i] = fmax(delta + fmin(delta, 1)*irandom(-1, 1), fmin(delta, 1));
	}

	Organism offspring(newCode);
	return offspring;
}

bool Organism::isHungry() const
{
	// Returns true if energy is below 80%
	if (m_energy < float (m_maxEnergy * 4 / 5))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Organism::takeTurn()
{
	int totalTaken = 0;

	totalTaken += 5*m_code[bodySize];
	totalTaken += 3*m_code[legSize];
	
	totalTaken /= 5;
	
	m_energy -= totalTaken;
}

void Organism::eat(const food &type, const int &rawEnergy)
{
	if(type == m_code[stomachType])
	{
		m_energy += rawEnergy;
	}
	else if(abs(m_code[stomachType] - type) == 1)
	{
		m_energy += rawEnergy * .7;
	}
	else
	{
		m_energy += rawEnergy * .1;
	}
}

void Organism::move(const int &x, const int &y)
{
	m_x += x;
	m_y += y;

	m_energy -= 1 * m_code[bodySize];
}
