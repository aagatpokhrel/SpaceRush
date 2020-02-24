#pragma once
#include "collision.h"

namespace Collision
{
	class BitmaskManager
	{
	public:
		~BitmaskManager() {
			std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
			for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter != end; iter++)
				delete[] iter->second;
		}

		sf::Uint8 GetPixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
			if (x > tex->getSize().x || y > tex->getSize().y)
				return 0;

			return mask[x + y * tex->getSize().x];
		}

		sf::Uint8* GetMask(const sf::Texture* tex) {
			sf::Uint8* mask;
			std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
			if (pair == Bitmasks.end())
			{
				sf::Image img = tex->copyToImage();
				mask = CreateMask(tex, img);
			}
			else
				mask = pair->second;

			return mask;
		}

		sf::Uint8* CreateMask(const sf::Texture* tex, const sf::Image& img) {
			sf::Uint8* mask = new sf::Uint8[tex->getSize().y * tex->getSize().x];

			for (unsigned int y = 0; y < tex->getSize().y; y++)
			{
				for (unsigned int x = 0; x < tex->getSize().x; x++)
					mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
			}

			Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));

			return mask;
		}
	private:
		std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
	};

	BitmaskManager Bitmasks;

	bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, std::shared_ptr<Spaceship>& sp2, sf::Uint8 AlphaLimit) {
		sf::FloatRect Intersection;
		if (sp1->getBounds().intersects(sp2->getBounds(), Intersection)) {
			sf::IntRect O1SubRect = sp1->getTextureRect();
			sf::IntRect O2SubRect = sp2->getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(sp1->getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(sp2->getTexture());

			// Loop through our pixels
			for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
				for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = sp1->getInverseTransform().transformPoint(i, j);
					sf::Vector2f o2v = sp2->getInverseTransform().transformPoint(i, j);

					// Make sure pixels fall within the sprite's subrect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, sp1->getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit&&
							Bitmasks.GetPixel(mask2, sp2->getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
						{
							return true;
						}

					}
				}
			}
		}
		return false;
	}
	bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, std::shared_ptr<Bullet>& bullet, sf::Uint8 AlphaLimit) {
		sf::FloatRect Intersection;
		if (bullet->getBounds().intersects(sp1->getBounds(), Intersection)) {
			sf::IntRect O1SubRect = bullet->getTextureRect();
			sf::IntRect O2SubRect = sp1->getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(bullet->getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(sp1->getTexture());

			// Loop through our pixels
			for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
				for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = bullet->getInverseTransform().transformPoint(i, j);
					sf::Vector2f o2v = sp1->getInverseTransform().transformPoint(i, j);

					// Make sure pixels fall within the sprite's subrect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, bullet->getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit&&
							Bitmasks.GetPixel(mask2, sp1->getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
						{
							return true;
						}

					}
				}
			}
		}
		return false;
	}

	bool PixelPerfectTest(std::shared_ptr<Spaceship>& sp1, std::shared_ptr<Asteroid>& as, sf::Uint8 AlphaLimit) {
		sf::FloatRect Intersection;
		if (as->getBounds().intersects(sp1->getBounds(), Intersection)) {
			sf::IntRect O1SubRect = as->getTextureRect();
			sf::IntRect O2SubRect = sp1->getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(as->getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(sp1->getTexture());

			// Loop through our pixels
			for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
				for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = as->getInverseTransform().transformPoint(i, j);
					sf::Vector2f o2v = sp1->getInverseTransform().transformPoint(i, j);

					// Make sure pixels fall within the sprite's subrect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, as->getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit&&
							Bitmasks.GetPixel(mask2, sp1->getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
						{
							return true;
						}

					}
				}
			}
		}
		return false;
	}

	bool PixelPerfectTest(std::shared_ptr<Asteroid>& as, std::shared_ptr<Bullet>& bullet, sf::Uint8 AlphaLimit) {
		sf::FloatRect Intersection;
		if (bullet->getBounds().intersects(as->getBounds(), Intersection)) {
			sf::IntRect O1SubRect = bullet->getTextureRect();
			sf::IntRect O2SubRect = as->getTextureRect();

			sf::Uint8* mask1 = Bitmasks.GetMask(bullet->getTexture());
			sf::Uint8* mask2 = Bitmasks.GetMask(as->getTexture());

			// Loop through our pixels
			for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
				for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

					sf::Vector2f o1v = bullet->getInverseTransform().transformPoint(i, j);
					sf::Vector2f o2v = as->getInverseTransform().transformPoint(i, j);

					// Make sure pixels fall within the sprite's subrect
					if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

						if (Bitmasks.GetPixel(mask1, bullet->getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit&&
							Bitmasks.GetPixel(mask2, as->getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
						{
							return true;
						}

					}
				}
			}
		}
		return false;
	}
}