#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCharacterSelection.h"
#include "ModuleTitleScreen.h"
#include "ModuleFadeToBlack.h"


ModuleTitleScreen::ModuleTitleScreen() 
{
	titlescreen.x = 0;
	titlescreen.y = 0;
	titlescreen.w = 224;
	titlescreen.h = 320;
}

ModuleTitleScreen::~ModuleTitleScreen()
{}

// Load assets
bool ModuleTitleScreen::Start()
{
	LOG("Loading title screen assets");
	bool ret = true;
	graphics = App->textures->Load("assets/screens/Title.png");

	App->audio->PlayMusic("assets/audio/music/gunbird-002_Title_Castle.ogg");
	insertcoin = App->audio->LoadWAV("assets/audio/sound/InsertCoin.wav");

	return ret;
}

bool ModuleTitleScreen::CleanUp()
{
	LOG("Destroying SDL audio");
	App->audio->StopMusic();
	App->audio->UnloadWAV(insertcoin);

	LOG("Unloading title screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleTitleScreen::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &titlescreen, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->fade->IsFading() == false) {
		App->audio->PlayWAV(insertcoin);
		App->fade->FadeToBlack(this, App->characterselection, 1.8);
	}

	return UPDATE_CONTINUE;
}