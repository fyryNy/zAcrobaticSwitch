// This file added in headers queue
// File: "Sources.h"
#include "resource.h"

namespace GOTHIC_ENGINE {
  int GetPlayerTalent(const zSTRING& talent)
  {
    auto sym = parser->GetSymbol(talent);
    if (!sym)
    {
      return Invalid;
    }

    return player->GetTalentSkill(sym->single_intdata);
  }

  void AcrobaticSwitch()
  {
    if (player->activeOverlays.Search(overlayName.data()) != Invalid)
    {
      player->RemoveOverlay(overlayName.data());
    }
    else
    {
      player->ApplyOverlay(overlayName.data());
    }

    if (player->GetAnictrl())
    {
      player->GetAnictrl()->InitAnimations();
    }
  }

  void Game_Entry() {
  }

  void Game_Init() {
    HotKey = GetKey(zoptions->ReadString("zAcrobaticSwitch", "HotKey", "KEY_P"));
  }

  void Game_Exit() {
  }

  void Game_PreLoop() {
  }

  void Game_Loop() {
    if (HotKey == Invalid)
    {
      return;
    }

    if (!ogame || ogame->singleStep || ogame->pause_screen || ogame->GetWorld()->csPlayer->GetPlayingGlobalCutscene() || !oCInformationManager::GetInformationManager().HasFinished())
    {
      return;
    }

    if (!player || player->IsUnconscious() || player->attribute[NPC_ATR_HITPOINTS] <= 0 || !player->GetEM()->IsEmpty(false) || !player->IsHuman() || player->interactMob || player->interactItem || player->GetBodyState() != BS_STAND || player->inventory2.IsOpen())
    {
      return;
    }

    if (!GetPlayerTalent("NPC_TALENT_ACROBAT"))
    {
      return;
    }

    if (zcon->IsVisible())
    {
      return;
    }

    if (zKeyToggled(HotKey))
    {
      AcrobaticSwitch();
    }
  }

  void Game_PostLoop() {
  }

  void Game_MenuLoop() {
  }

  // Information about current saving or loading world
  TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

  void Game_SaveBegin() {
  }

  void Game_SaveEnd() {
  }

  void LoadBegin() {
  }

  void LoadEnd() {
  }

  void Game_LoadBegin_NewGame() {
    LoadBegin();
  }

  void Game_LoadEnd_NewGame() {
    LoadEnd();
  }

  void Game_LoadBegin_SaveGame() {
    LoadBegin();
  }

  void Game_LoadEnd_SaveGame() {
    LoadEnd();
  }

  void Game_LoadBegin_ChangeLevel() {
    LoadBegin();
  }

  void Game_LoadEnd_ChangeLevel() {
    LoadEnd();
  }

  void Game_LoadBegin_Trigger() {
  }

  void Game_LoadEnd_Trigger() {
  }

  void Game_Pause() {
  }

  void Game_Unpause() {
  }

  void Game_DefineExternals() {
  }

  void Game_ApplyOptions() {
  }

  /*
  Functions call order on Game initialization:
    - Game_Entry           * Gothic entry point
    - Game_DefineExternals * Define external script functions
    - Game_Init            * After DAT files init

  Functions call order on Change level:
    - Game_LoadBegin_Trigger     * Entry in trigger
    - Game_LoadEnd_Trigger       *
    - Game_Loop                  * Frame call window
    - Game_LoadBegin_ChangeLevel * Load begin
    - Game_SaveBegin             * Save previous level information
    - Game_SaveEnd               *
    - Game_LoadEnd_ChangeLevel   *

  Functions call order on Save game:
    - Game_Pause     * Open menu
    - Game_Unpause   * Click on save
    - Game_Loop      * Frame call window
    - Game_SaveBegin * Save begin
    - Game_SaveEnd   *

  Functions call order on Load game:
    - Game_Pause              * Open menu
    - Game_Unpause            * Click on load
    - Game_LoadBegin_SaveGame * Load begin
    - Game_LoadEnd_SaveGame   *
  */

#define AppDefault True
  CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
    Enabled(AppDefault) Game_Entry,
    Enabled(AppDefault) Game_Init,
    Enabled(AppDefault) Game_Exit,
    Enabled(AppDefault) Game_PreLoop,
    Enabled(AppDefault) Game_Loop,
    Enabled(AppDefault) Game_PostLoop,
    Enabled(AppDefault) Game_MenuLoop,
    Enabled(AppDefault) Game_SaveBegin,
    Enabled(AppDefault) Game_SaveEnd,
    Enabled(AppDefault) Game_LoadBegin_NewGame,
    Enabled(AppDefault) Game_LoadEnd_NewGame,
    Enabled(AppDefault) Game_LoadBegin_SaveGame,
    Enabled(AppDefault) Game_LoadEnd_SaveGame,
    Enabled(AppDefault) Game_LoadBegin_ChangeLevel,
    Enabled(AppDefault) Game_LoadEnd_ChangeLevel,
    Enabled(AppDefault) Game_LoadBegin_Trigger,
    Enabled(AppDefault) Game_LoadEnd_Trigger,
    Enabled(AppDefault) Game_Pause,
    Enabled(AppDefault) Game_Unpause,
    Enabled(AppDefault) Game_DefineExternals,
    Enabled(AppDefault) Game_ApplyOptions
  );
}