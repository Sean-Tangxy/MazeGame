#pragma once

#include <utils.h>
#include <set>

class IMAGE {
public:
	IMAGE(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID = AnimID::NO_ANIMATION);
	IMAGE();
	~IMAGE();

	IMAGE(const IMAGE& other) = delete;
	IMAGE(IMAGE&& other) = delete;
	IMAGE& operator=(const IMAGE& other) = delete;
	IMAGE& operator=(IMAGE&& other) = delete;
	virtual ~IMAGE();

	bool operator==(const IMAGE& other) const;

	void Update();
	void OnClick();

	int GetX() const;
	int GetY() const;
	int getwidth() const;
	int getheight() const;

	void MoveTo(int x, int y);

	AnimID GetCurrentAnimation() const;
	void ChangeImage(ImageID imageID);
	void PlayAnimation(AnimID animID);

	friend class GameManager;

private:
	ImageID m_imageID;
	int m_x;
	int m_y;
	LayerID m_layer;
	int m_width;
	int m_height;
	AnimID m_animID;
	std::size_t m_currentFrame;

public:
	template<typename Func>
	static void DisplayAllObjects(Func displayAndAnimateFunc) {
		for (int layer = MAX_LAYERS - 1; layer >= 0; --layer) {
			for (auto& obj : GetObjects(static_cast<LayerID>(layer))) {
				obj->m_currentFrame = displayAndAnimateFunc(obj->m_imageID, obj->m_animID, obj->m_x, obj->m_y, obj->m_currentFrame);
			}
		}
	}

	static void ClickAt(int x, int y) {
		for (int layer = 0; layer < MAX_LAYERS; ++layer) {
			for (auto& obj : GetObjects(static_cast<LayerID>(layer))) {
				if (std::abs(x - obj->m_x) <= obj->m_width / 2 && std::abs(y - obj->m_y) <= obj->m_height / 2) {
					obj->OnClick();
					return;
				}
			}
		}
	}

	static std::set<IMAGE*>& GetObjects(LayerID layer);
};