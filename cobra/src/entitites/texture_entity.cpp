#include "game_entity.h"
#include "texture_entity.h"

void Texture_Entity::render() const
{
	Texture_Component* texture_component = get_texture_component();
	if (texture_component != nullptr) {
		get_texture_component()->render();
	}

	for (const Collider2D* collider : m_colliders)
	{
		if (collider != nullptr)
		{
			collider->render(m_renderer);
		}
	}
}
