SDL 1.2 imgui backend
=====================
Moved to GitLab https://gitlab.com/wildangelcult/sdl1-2-imgui-backend

Vytvářel jsem hacknutého klienta pro Assault Cube a zjistil, že neexistuje žádný ImGui backend pro SDL 1.2. Tak tady jeden je.

Je nedodělaný, chybí pár klíčových věcí, ale na základní práci s ImGui skvěle vystačí.

Poznámka k používaní
--------------------

Argument pro `NewFrame` je návratová hodnota z `SDL_SetVideoMode`, v Assault Cube je to globální proměnná `screen`.
