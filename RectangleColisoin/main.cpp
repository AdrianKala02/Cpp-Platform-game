
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "ObjCreator.hpp"
#include "ResourcePath.hpp"
#include "Hero.hpp"
#include "AnimateHandler.hpp"
#include "ColisionHandler.hpp"
#include "Map.hpp"
#include "InfoBlok.hpp"
#include "Blok.hpp"
#include "Item.hpp"
#include <filesystem>
#include "MyView.hpp"
#include "Enemy.hpp"
#include "Gun.hpp"
#include "Bullet.hpp"
#include <fstream>
#include "SpecialBlok.hpp"
std::string loadTextFromFile(std::string const& url){
    std::ifstream plik(url);
    if (!plik.is_open()) {std::cout << "Nie można otworzyć pliku";}
    std::string tekst;
    std::string linia;
    while (std::getline(plik, linia)) {tekst += linia + "\n";}
    plik.close();
    return tekst;
}
bool renderViewScope(sf::View const& view,ObjCreator& obj){
    if(view.getCenter().x-view.getSize().x/2.f-32<=obj.shape.getPosition().x+obj.shape.getSize().x/2.f&&
       view.getCenter().x+view.getSize().x/2.f>=obj.shape.getPosition().x-obj.shape.getSize().x/2.f&&
       view.getCenter().y-view.getSize().y/2.f-32<=obj.shape.getPosition().y+obj.shape.getSize().y/2.f&&
       view.getCenter().y+view.getSize().y/2.f>=obj.shape.getPosition().y-obj.shape.getSize().y/2.f)
    {return true;}
    
    else{return false;}
}
bool renderViewScope(sf::View const& view,sf::RectangleShape& obj){
    if(view.getCenter().x-view.getSize().x/2.f-32<=obj.getPosition().x+obj.getSize().x/2.f&&
       view.getCenter().x+view.getSize().x/2.f>=obj.getPosition().x-obj.getSize().x/2.f&&
       view.getCenter().y-view.getSize().y/2.f-32<=obj.getPosition().y+obj.getSize().y/2.f&&
       view.getCenter().y+view.getSize().y/2.f>=obj.getPosition().y-obj.getSize().y/2.f)
    {return true;}
    
    else{return false;}
}
void doIt(sf::Texture& texture,std::string const& url){
    //przycięcie ścieżki i napisanie tylko użytego pliku
    std::__fs::filesystem::path filePath(url);
    texture.loadFromFile(url);
    std::cout<<"\nTekstura stworzona! "<<filePath.filename().string()<<" Rozmiar: "<<texture.getSize().x<<" | "<<texture.getSize().y<<"\n";
};

void myicon(sf::RenderWindow& win,std::string const& imgurl){
    sf::Image icon;
    if (!icon.loadFromFile(imgurl)) {
        return EXIT_FAILURE;
    }
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
};


///MAIN



int main(int, char const**){
    //string z dodaniem do linku gdzie są grafiki
    std::string firstString="/Users/adriankala/Desktop/studia/GameV1/doneSP/";
    
    sf::Font font;
    //font nie jest mojego autorstwa,
    //https://www.dafont.com/minecraftia.font
    if (!font.loadFromFile(firstString+"/Minecraftia.ttf")) {
        std::cerr <<"Błąd ładowania czcionki z pliku: "<<firstString+"/Minecraftia.ttf";
    }
    //bloczek do informacji  o stanie mecha itd
    InfoBlok infoTESR(font,16,1,0,0,sf::Vector2f(400,200),sf::Color(0,0,0,160),sf::Color(0,0,0),-2);
    infoTESR.text.setFillColor(sf::Color(131,179,107));
    //backgroud dla mapy, tak było wygodniej
    InfoBlok RectForMinimap(font, 0,1,0,0, sf::Vector2f(370,205), sf::Color(70,100,128), sf::Color(2,2,2), -4);

    
    //PopBlok z informacją na wstępie, jak się steruje i takie tam
    InfoBlok BlokInformacyjny(font,24,0.5,-8,-16,sf::Vector2f(700,350),sf::Color(0,0,0,160),sf::Color(0,0,0),-2);
    BlokInformacyjny.text.setString(loadTextFromFile(firstString +"teksty/info.txt"));
    BlokInformacyjny.text.setFillColor(sf::Color(131,179,107));
    BlokInformacyjny.setPositionManual(sf::Vector2f(0,0));

//    InfoBlok BlokInformacyjny(font,24,0.5,-8,-16,sf::Vector2f(550,250),sf::Color(0,0,0,160),sf::Color(0,0,0),-2);
//    BlokInformacyjny.text.setString(loadTextFromFile(firstString +"teksty/info.txt"));
//    BlokInformacyjny.text.setFillColor(sf::Color(131,179,107));
//    BlokInformacyjny.setPositionManual(sf::Vector2f(150,160));
    
    
    
    
    InfoBlok GameOverBlok(font,130,0.5,-8,-16,sf::Vector2f(1920,1080),sf::Color(0,0,0,160),sf::Color(0,0,0),-2);
    GameOverBlok.text.setString("GAME OVER");
    GameOverBlok.text.setFillColor(sf::Color(131,179,107));

    ///INICIAL
    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GameTest"); //okienko
    window.setFramerateLimit(120); //ustawia limit klatek
    window.setKeyRepeatEnabled(false);
    //główna kamera
    MyView heroView(window,0.03f);
    heroView.view.zoom(1.0f);
    
    //MINIMAPA
    sf::View minimapView(sf::FloatRect(0.f, 0.f, 1920, 1080));
    minimapView.zoom(4);
    sf::FloatRect minimapViewport(0.75f, 0.f, 0.25f, 0.25f);
    minimapView.setViewport(minimapViewport);
    

    sf::Mouse mouse; //muszka
    
    sf::Cursor cursorCelownik1;
    sf::Texture crTCelownik1;
    crTCelownik1.loadFromFile(firstString+"cursor/celownik1.png");
    cursorCelownik1.loadFromPixels(crTCelownik1.copyToImage().getPixelsPtr(), sf::Vector2u(32,32), sf::Vector2u(16,16));
    
    sf::Cursor cursorCelownik2;
    sf::Texture crTCelownik2;
    crTCelownik2.loadFromFile(firstString+"cursor/celownik2.png");
    cursorCelownik2.loadFromPixels(crTCelownik2.copyToImage().getPixelsPtr(), sf::Vector2u(32,32), sf::Vector2u(16,16));

    
    sf::Cursor cursorPointer;
    sf::Texture crTPointer;
    crTPointer.loadFromFile(firstString+"cursor/pointer.png");
    cursorPointer.loadFromPixels(crTPointer.copyToImage().getPixelsPtr(), sf::Vector2u(32,32), sf::Vector2u(10,1));

    
    sf::Cursor cursorMFG;
    sf::Texture crTMFG;
    crTMFG.loadFromFile(firstString+"cursor/magnifingGlass.png");
    cursorMFG.loadFromPixels(crTMFG.copyToImage().getPixelsPtr(), sf::Vector2u(32,32), sf::Vector2u(16,16));

    window.setMouseCursor(cursorCelownik1);
    
    
    
    
    
    
    
    // Set the Icon
    myicon(window,firstString+"logo.png");
    
    

    
    sf::Clock heroJumptime; //zegar skoku
    sf::Clock dt_clock; //zegar ogólny tzw deltaTime
    float dt; //odcinek czasu z deltaTime

    sf::Clock animateCLOCK; //zegar dla animacji przedmiotów
    sf::Clock hCLOCK; //zegar dla animacji postaci
    sf::Clock enemyClock; //zegar dla animacji przeciwników

    
    ///shape
    ColisionHandler Kolizje; //inicializacja klasy w której są funkcje do sprawdzania i wykonywania kolizji
    AnimateHandler Animacje;
    
    
    //kolory dla różnych rzeczy ładowanych z mapy:
    //odcienie czarnego: bloki,
    //odcienie czerwonego: przeciwnicy,
    //odcienie niebieskiego: itemy,
    //odcienie zielonego:
    //odcienie żłótego: miejsca/bloki specjalne(robią coś więcej niż tylko blokują przejście),
    //odcienie magenty:
    //odcienei cyjanu:
    
    //KOLOR SPECJALNY     hero.mapIdColor=sf::Color(129,163,142);
    // bez ustawienia tego koloru pozycja bohatera jest na 100,100
    
    //red
    sf::Color red1(255, 0, 0);
    sf::Color red2(200, 0, 0);
    sf::Color red3(150, 0, 0);
    sf::Color red4(120, 0, 0);
    sf::Color red5(100, 0, 0);
    sf::Color red6(70, 0, 0);
    //green
    sf::Color green1(0, 255, 0);
    sf::Color green2(0, 200, 0);
    sf::Color green3(0, 150, 0);
    sf::Color green4(0, 120, 0);
    sf::Color green5(0, 100, 0);
    sf::Color green6(0, 70, 0);
    //blue
    sf::Color blue1(0, 0, 255);
    sf::Color blue2(0, 0, 200);
    sf::Color blue3(0, 0, 150);
    sf::Color blue4(0, 0, 120);
    sf::Color blue5(0, 0, 100);
    sf::Color blue6(0, 0, 70);
    //black
    sf::Color black1(0, 0, 0);
    sf::Color black2(38, 38, 38);
    sf::Color black3(51, 51, 51);
    sf::Color black4(77, 77, 77);
    sf::Color black5(102, 102, 102);
    sf::Color black6(186, 186, 186);
    //yellow
    sf::Color yellow1(255, 255, 0);
    sf::Color yellow2(220, 220, 0);
    sf::Color yellow3(200, 200, 0);
    sf::Color yellow4(150, 150, 0);
    sf::Color yellow5(100, 100, 0);
    sf::Color yellow6(70, 70, 0);
    //magenta
    sf::Color magenta1(255, 0, 255);
    sf::Color magenta2(220, 0, 220);
    sf::Color magenta3(200, 0, 200);
    sf::Color magenta4(150, 0, 150);
    sf::Color magenta5(100, 0, 100);
    sf::Color magenta6(70, 0, 70);
    //cyjan
    sf::Color cyjan1(0, 255, 255);
    sf::Color cyjan2(0, 220, 220);
    sf::Color cyjan3(0, 200, 200);
    sf::Color cyjan4(0, 150, 150);
    sf::Color cyjan5(0, 100, 100);
    sf::Color cyjan6(0, 70, 70);
    /*| Tworzenie bloków*/
    /*v*/
    
    
    
    
    
    sf::Texture textureA;
    doIt(textureA,firstString+"bloks/blokTESTa.png");
    Blok blokTypuA(textureA,11);
    blokTypuA.mapIdColor=black1;
    
    
    sf::Texture textureB;
    doIt(textureB,firstString+"bloks/blokTESTb.png");
    Blok blokTypuB(textureB,12);
    blokTypuB.mapIdColor=black2;

    sf::Texture textureC;
    doIt(textureC,firstString+"bloks/blokTESTc.png");
    Blok blokTypuC(textureC,13);
    blokTypuC.mapIdColor=black3;
    
    sf::Texture textureD;
    doIt(textureD,firstString+"bloks/blokTESTd.png");
    Blok blokTypuD(textureD,14);
    blokTypuD.mapIdColor=black4;
    

    sf::Texture sp1Texture;
    doIt(sp1Texture, firstString+"winPointv2.png");
    SpecialBlok sp1(sp1Texture,11,32,64);
    sp1.spritesSheetPos=sf::IntRect(0,0,32,64);
    sp1.sprite.setTextureRect(sp1.spritesSheetPos);
    sp1.mapIdColor=yellow1;
    
    sf::Texture healStationTexture;
    doIt(healStationTexture, firstString+"healStation.png");
    SpecialBlok healStation(healStationTexture,12,64,64);
    healStation.mapIdColor=yellow2;
    

    
    /*| Tworzenie itemów*/
    /*v*/
    sf::Texture monetaTexture;
    doIt(monetaTexture,firstString+"items/poin-Sheet.png");
    Item moneta(monetaTexture,11,1,'a');
    moneta.mapIdColor=blue1;

    sf::Texture chipTexture;
    doIt(chipTexture,firstString+"items/dropA-Sheet.png");
    Item chip(chipTexture,12,20,'x');
    chip.mapIdColor=blue2;
    
    /*| Tworzenie przeciwników*/
    /*v*/
    sf::Texture enemy1;
    doIt(enemy1, firstString+"enemys/Slime-Sheet.png");
    Enemy enemyBLOB(enemy1, 5, 2, 5, 100, 2, -1, "blob", 1);
    enemyBLOB.mapIdColor=red1;
    enemyBLOB.enemyBar.text.setFont(font);
    
    sf::Texture monsterRoboTexture;
    doIt(monsterRoboTexture, firstString+"enemys/MonsterRobo-Sheet.png");
    Enemy monsterRobo(monsterRoboTexture, 30, 6, 4, 170, 4, -1, "MonsterRobo",6);
    monsterRobo.jumpPower=60;
    monsterRobo.mapIdColor=red2;
    monsterRobo.enemyBar.text.setFont(font);
    
    sf::Texture xavTexture;
    doIt(xavTexture, firstString+"enemys/Xav-Sheet.png");
    Enemy xav(xavTexture, 10, 3, 4, 170, 4, -1, "Xav-008",2);
    xav.jumpPower=25;
    xav.mapIdColor=red3;
    xav.enemyBar.text.setFont(font);
    
    sf::Texture slimVeinTexture;
    doIt(slimVeinTexture, firstString+"enemys/slimeVein-Sheet.png");
    Enemy slimVein(slimVeinTexture, 70, 10, 4, 300, 10, -1, "slimVein",4);
    slimVein.jumpPower=25;
    slimVein.mapIdColor=red4;
    slimVein.enemyBar.text.setFont(font);
    slimVein.shape.setScale(2, 2);
    slimVein.sprite.setScale(2, 2);
    
    sf::Texture hostTexture;
    doIt(hostTexture, firstString+"enemys/host-Sheet.png");
    Enemy host(hostTexture, 230, 20, 4, 200, 10, -1, "host",7);
    host.jumpPower=25;
    host.mapIdColor=red5;
    host.enemyBar.text.setFont(font);
    host.shape.setScale(3, 3);
    host.sprite.setScale(3, 3);
    
    
    /*| Tworzenie broni i pocisków*/
    /*v*/
    
    
    sf::Texture laserBulletTexture;
    laserBulletTexture.create(32, 32);
    laserBulletTexture.loadFromFile(firstString+"bulets/laserBullet.png");
    Bullet laserBullet(laserBulletTexture,3);
    laserBullet.shape.setSize(sf::Vector2f(16,16));
    laserBullet.sprite.setOrigin(16, 16);
    laserBullet.shape.setOrigin(laserBullet.shape.getSize()/2.f);

    
    sf::Texture laserGunTexture;
    laserGunTexture.create(32, 32);
    laserGunTexture.loadFromFile(firstString+"guns/laserGUN.png");

    Gun laserGun(laserGunTexture,laserBullet,32,32,5,0.5,6,10,7,false);
    laserGun.shape.setOrigin(16, 16);
    laserGun.sprite.setOrigin(16, 16);
    laserGun.nazwaBroni="LG-883";
    
    
    
    sf::Texture magicBulletTexture;
    magicBulletTexture.create(32, 32);
    magicBulletTexture.loadFromFile(firstString+"bulets/magicBall.png");
    Bullet magicBullet(magicBulletTexture,3);
    magicBullet.shape.setSize(sf::Vector2f(16,16));
    magicBullet.sprite.setOrigin(16, 16);
    magicBullet.shape.setOrigin(magicBullet.shape.getSize()/2.f);

    
    sf::Texture XentroGunTexture;
    XentroGunTexture.create(32, 32);
    XentroGunTexture.loadFromFile(firstString+"guns/gun1.png");
    Gun XentroGun(XentroGunTexture,magicBullet,32,32,10,0.2,3,6,20,true);
    XentroGun.shape.setOrigin(16, 16);
    XentroGun.sprite.setOrigin(16, 16);
    XentroGun.nazwaBroni="Xentro";
    
    
    sf::Texture harpoonTexture;
    harpoonTexture.create(32, 32);
    harpoonTexture.loadFromFile(firstString+"bulets/harpoon.png");
    Bullet harpoonBullet(harpoonTexture,3);
    harpoonBullet.shape.setSize(sf::Vector2f(16,16));
    harpoonBullet.sprite.setOrigin(16, 16);
    harpoonBullet.shape.setOrigin(harpoonBullet.shape.getSize()/2.f);

    
    sf::Texture harpoonCanonTexture;
    harpoonCanonTexture.create(32, 32);
    harpoonCanonTexture.loadFromFile(firstString+"guns/harpoonCanon.png");
    Gun harpoonCanon(harpoonCanonTexture,harpoonBullet,32,32,10,2,0.3,14,0,false);
    harpoonCanon.shape.setOrigin(16, 16);
    harpoonCanon.sprite.setOrigin(16, 16);
    harpoonCanon.nazwaBroni="harpoonCanon";
    
    
    sf::Texture bulletTexture;
    bulletTexture.create(32, 32);
    bulletTexture.loadFromFile(firstString+"bulets/bullet.png");
    Bullet bullet(bulletTexture,5);
    bullet.shape.setSize(sf::Vector2f(16,16));
    bullet.sprite.setOrigin(16, 16);
    bullet.shape.setOrigin(bullet.shape.getSize()/2.f);
    
    
    sf::Texture minigunTexture;
    minigunTexture.create(96, 32);
    minigunTexture.loadFromFile(firstString+"guns/minigun.png");
    Gun minigun(minigunTexture,bullet,96,32,100,0.1,10,30,50,false);
    minigun.shape.setOrigin(32, 16);
    minigun.sprite.setOrigin(32, 16);
    minigun.nazwaBroni="minigun";
    
    
    /*| Tworzenie postaci*/
    /*v*/
    sf::Texture dlabohatera;
    doIt(dlabohatera, firstString+"hero/sheetRB.png");
    Hero hero(dlabohatera,harpoonCanon);
    hero.shape.setOutlineColor(sf::Color::Black);
    hero.shape.setPosition(100, 100);
    hero.mapIdColor=sf::Color(129,163,142);
    hero.addToEQ(harpoonCanon);
    hero.addToEQ(laserGun);
    hero.addToEQ(XentroGun);
//    hero.addToEQ(XentroGun);
    hero.addToEQ(minigun);
    hero.points=100;
//    hero.addToEQ(laserGun);
//    hero.addToEQ(laserGun);
//    hero.addToEQ(laserGun);

    
    

    sf::Texture slotTexture;
    slotTexture.loadFromFile(firstString+"itemInventoryBox.png");
    ObjCreator slot(slotTexture,32,32);
    slot.sprite.setScale(2,2);
    slot.shape.setPosition(sf::Vector2f(100,100));
    
    sf::Text slotVal;
    slotVal.setCharacterSize(24);
    slotVal.setFont(font);
    std::vector<sf::Text>slotsValNO1;
    std::vector<ObjCreator> slotyNO1;
    for(auto& bron:hero.bronie){
        slotyNO1.push_back(slot);
        slotVal.setString(std::to_string(bron.wymaganePunkty));
        slotsValNO1.push_back(slotVal);
    }
    //aby widzieś ile kosztuje dana broń
    
    
    
    
    
    std::vector<Blok> blokiNO1;
    std::vector<Item> itemNO1;
    std::vector<Enemy> enemyNO1;
    std::vector<SpecialBlok> specialneBlokiNO1;
    
    
    
    std::vector<Blok> blokiMapy;
    blokiMapy.push_back(blokTypuA);
    blokiMapy.push_back(blokTypuB);
    blokiMapy.push_back(blokTypuC);
    blokiMapy.push_back(blokTypuD);
    
    std::vector<Item> itemyMapy;
    itemyMapy.push_back(moneta);
    itemyMapy.push_back(chip);
    
    std::vector<Enemy> enemyMapy;
    enemyMapy.push_back(enemyBLOB);
    enemyMapy.push_back(monsterRobo);
    enemyMapy.push_back(xav);
    enemyMapy.push_back(host);
    enemyMapy.push_back(slimVein);
    
    std::vector<SpecialBlok> specialneBlokiMapy;
    specialneBlokiMapy.push_back(sp1);
    specialneBlokiMapy.push_back(healStation);
    
    const float gridSize=32.f; //rozmiar grida czyli jaki ma być rozmiar wszystkich bloków
    
    /*| wczytywanie danych z obrazka (TILE MAP)*/
    /*v*/
    Map mapkaNO1;
    //mapkaNO1.imgTEST(firstString+"maps/maptestc.png");
    mapkaNO1.advancedMapLoader(blokiNO1, itemNO1, enemyNO1,specialneBlokiNO1, blokiMapy, itemyMapy, enemyMapy,specialneBlokiMapy,hero, firstString+"maps/mapFinal.png", gridSize);

    bool colisionData=false;
    bool metaData =true;
    bool toggleforkeyK=false;
    bool toggleforkeyI=false;
    bool minimapON=false;
    bool toggleforkeyB=true;

                                                    int reqPointsToWin=70;
    int sprPoints=0;
    for(auto &item: itemNO1){
        sprPoints+=item.point;
    }
    if(reqPointsToWin>sprPoints){
        reqPointsToWin=sprPoints;
    }
    bool wygrana=false;
    sf::Clock blockTimer;
    BlokInformacyjny.setPositionManual(hero.shape.getPosition()-sf::Vector2f(32*10,32*11));

    ///UPDATE
    while (window.isOpen()){

    dt= dt_clock.restart().asSeconds();
        
    // Process events
    sf::Event event;
    while (window.pollEvent(event)){
        
    if (event.type == sf::Event::Closed) {window.close();}
        
        if(hero.health>0){
        heroView.zoomView(event, window);
        if (event.type == sf::Event::KeyPressed){
            
            
            
            if(event.key.scancode == sf::Keyboard::Scan::H){
                if(hero.rodzajZawieszenia==1){
                    hero.rodzajZawieszenia=2;
                    hero.spritesSheetPos.top=64;
                }else if(hero.rodzajZawieszenia==2){
                    hero.rodzajZawieszenia=1;
                    hero.spritesSheetPos.top=0;
                }
            }

            if (event.key.scancode == sf::Keyboard::Scan::K){
                if(toggleforkeyK){
                    colisionData=false;
                    toggleforkeyK=false;
                }else{
                    colisionData=true;
                    toggleforkeyK=true;
                }}
            else if(event.key.scancode == sf::Keyboard::Scan::I){
                if(toggleforkeyI){
                    metaData=false;
                    toggleforkeyI=false;
                }else{
                    metaData=true;
                    toggleforkeyI=true;
                }}
            else if(event.key.scancode == sf::Keyboard::Scan::B){
                if(toggleforkeyB){
                    toggleforkeyB=false;
                }else{
                    toggleforkeyB=true;
                }
            }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                if( minimapON){
                 minimapON=false;
                }else
                    minimapON=true;
             }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
                minimapView.zoom(1.1);
            }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
                minimapView.zoom(0.9);
            }
            

        }}
    }
        if(hero.health>0&&!wygrana){

        hero.chooser(window, mouse, heroView);
        hero.wybranaBron->update(window,mouse,hero.shape,heroView);

            

            
            
            
            
    //"nadaje" akceleracje ale nie porusza postacią gdyż najpier trzeba sprawdzić czy postać nie wbije się w blok
    hero.moveMe(dt);
        
        for(auto &enemy :enemyNO1){
            enemy.heroPos=hero.shape.getPosition();
            enemy.HeroesHealth=hero.health;
            enemy.moveMe(dt);
            if(enemy.nextPos.intersects(hero.shape.getGlobalBounds())&&
               enemy.timeChargeAttack.getElapsedTime().asSeconds()>enemy.timeBetweenAttacks){
                hero.health-=enemy.damage;
                enemy.timeChargeAttack.restart();
            }
        }
        
        //sprawdza wszystkie bloki w vektorze walls czy są obok postaci i jak jest to czy koliduje z nią, jeśli tak to ma "wyzerować" akcelerację w danym kierunku i ma tepnąć postać przed tym blokiem.
        for(auto &blok :blokiNO1){
            sf::FloatRect wallBounds= blok.shape.getGlobalBounds();
            //*->*//sprawdza odległość
            
            //blokowanie przeciwników na blokach
            for(auto &enemy :enemyNO1){
                if(enemy.nextPos.intersects(wallBounds)){
                    Kolizje.enemyToObj(enemy, blok);
                    Kolizje.forJumpEnemy(enemy, blok);
                }
            }
            if((hero.nextPos.left-gridSize<=wallBounds.left)&&(hero.nextPos.left+gridSize>=wallBounds.left)&&(hero.nextPos.top-gridSize<=wallBounds.top)&&(hero.nextPos.top+gridSize>=wallBounds.top)){
                blok.shape.setOutlineColor(sf::Color::Yellow);
                //*->*//sprawdza czy postać koliduje z blokiem
                if(hero.nextPos.intersects(wallBounds)){
                    
                    blok.shape.setOutlineColor(sf::Color::Red);
                //*->*// ustawia postać odpowiednio wzgędem tego bloku
                Kolizje.objToboj(hero, blok);
                Kolizje.forJump(hero, blok);
                }
                if(blok.id==12&&blockTimer.getElapsedTime().asSeconds()>0.5){
                    hero.health-=1;
                    blockTimer.restart();
                }
                if(blok.id==13){
                    hero.movementspeed=100;
                    }
                else{hero.movementspeed=hero.maxmovementspeed;}
                if(blok.id==14){
                    blok.shape.move(0, 2);
                    blok.sprite.setPosition(blok.shape.getPosition());
                }
                
                
            }else{
                blok.shape.setOutlineColor(sf::Color::Transparent);
            }
        }
            
            for(auto& spb: specialneBlokiNO1){
                
                    if(spb.id==11&&hero.points>=reqPointsToWin){
                        spb.spritesSheetPos=sf::IntRect(32,0,32,64);
                        spb.sprite.setTextureRect(spb.spritesSheetPos);
                        if(hero.shape.getGlobalBounds().intersects(spb.shape.getGlobalBounds())){
                        if(hero.points>=reqPointsToWin){
                        wygrana=true;
                            
                        }}
                    }else if(hero.shape.getGlobalBounds().intersects(spb.shape.getGlobalBounds())){
                        
                        
                        if(spb.id==12&&blockTimer.getElapsedTime().asSeconds()>0.3&&hero.health<hero.maxhealth){
                        hero.health+=1;
                            blockTimer.restart();
                    }
                    }
            }
        hero.update(window,mouse,heroView);

            for(auto &enemy :enemyNO1){
                    enemy.update();
            }
            
            
            for (auto& bronNr : hero.bronie) {
                for (auto& pociskNr : bronNr.magazine) {
                    
                    for (auto& enemy : enemyNO1) {
                        if (pociskNr.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
                            pociskNr.colidet = true;
                            enemy.health -= pociskNr.damage;
                        }
                    }
                    for (auto& wall : blokiNO1) {
                        if (pociskNr.shape.getGlobalBounds().intersects(wall.shape.getGlobalBounds())) {
                            pociskNr.colidet = true;
                        }
                    }
                }
            }

            for(auto& item : itemNO1){
                if(
                   hero.shape.getGlobalBounds().contains(item.shape.getGlobalBounds().getPosition().x+(item.shape.getGlobalBounds().width/2),item.shape.getGlobalBounds().getPosition().y+(item.shape.getGlobalBounds().height/2))){
                    hero.points+=item.point;
                    item.colected=true;
                }
            }
            
            
            
            
            
            itemNO1.erase(std::remove_if(itemNO1.begin(), itemNO1.end(), [](const Item& item) {
                return item.colected;
            }), itemNO1.end());
            
            enemyNO1.erase(std::remove_if(enemyNO1.begin(), enemyNO1.end(), [](const Enemy& enemy) {
                return enemy.health <= 0;
            }), enemyNO1.end());
            
            
            for(int i=0;i<hero.bronie.size();i++){
                hero.bronie[i].magazine.erase(std::remove_if(hero.bronie[i].magazine.begin(), hero.bronie[i].magazine.end(), [](const Bullet& bullet) {
                    return bullet.colidet;
                }), hero.bronie[i].magazine.end());
            }
            
            
            infoTESR.update(heroView,XPos::Left,YPos::Bottom);

            for(int i =0;i<hero.bronie.size();i++){
                slotyNO1[i].sprite.setScale(heroView.zoomFactor*3,heroView.zoomFactor*3);
                slotyNO1[i].shape.setPosition(infoTESR.rectangle.getPosition().x+i*48*heroView.zoomFactor,
                                              infoTESR.rectangle.getPosition().y-50*heroView.zoomFactor);
                
                slotyNO1[i].sprite.setPosition(slotyNO1[i].shape.getPosition());
                
                slotsValNO1[i].setScale(heroView.zoomFactor*0.5,heroView.zoomFactor*0.5);
                slotsValNO1[i].setPosition(infoTESR.rectangle.getPosition().x+i*48*heroView.zoomFactor,
                                           infoTESR.rectangle.getPosition().y-50*heroView.zoomFactor);

                
                
                if(!hero.bronie[i].uzywana){
                hero.bronie[i].setRot(-45);
                hero.bronie[i].setPos(sf::Vector2f(
                                      slotyNO1[i].sprite.getPosition().x+slotyNO1[i].sprite.getGlobalBounds().width/2,
                                      slotyNO1[i].sprite.getPosition().y+slotyNO1[i].sprite.getGlobalBounds().height/2));
                hero.bronie[i].shape.setScale(heroView.zoomFactor, heroView.zoomFactor);
                hero.bronie[i].sprite.setScale(heroView.zoomFactor, heroView.zoomFactor);
                }
                
                else{
                    hero.bronie[i].shape.setScale(1, 1);
                    hero.bronie[i].sprite.setScale(1, 1);
                }
            }

            

            RectForMinimap.update(heroView,XPos::Right,YPos::Top);
            heroView.moveView(hero.shape);
            minimapView.setCenter(heroView.view.getCenter());

        ///Item maxout
            
        ///Screen info

std::ostringstream p1;p1<<"Pozycja myszy: ";
std::ostringstream p2;p2<<"Pozycja mecha: ";
std::ostringstream p3;p3<<"Czy mech moze skoczyc: ";
std::ostringstream p4;p4<<"Grawitacja: ";
std::ostringstream p5;p5<<"Staty: ";
std::ostringstream p6;p6<<"ZOOM: ";
std::ostringstream p7;p7<<"Bron: ";
std::ostringstream p8;p8<<"Reload Time: ";
            
            
p1<<mouse.getPosition(window).x<<" | "<<mouse.getPosition(window).y<<"\n";
p2<<std::fixed<<std::setprecision(2)<<hero.shape.getPosition().x<<" | "<<std::fixed<<std::setprecision(2)<<hero.shape.getPosition().y<<"\n";
            if(hero.canJump){p3<<"tak"<<"\n";}else{p3<<"nie"<<"\n";};
p4<<std::fixed<<std::setprecision(2)<<hero.velocity.y<<"\n";
p5<<"HP: "<<hero.health<<" /"<<hero.maxhealth<<" Punkty: "<<hero.points<<"\n";
p6<<std::fixed<<std::setprecision(2)<<heroView.zoomFactor<<"\n";
p7<<hero.wybranaBron->nazwaBroni<<" Dmg: "<<hero.wybranaBron->naboj.damage<<" Ammo: "<<hero.wybranaBron->ammoMag<<"/"<<hero.wybranaBron->ammoCap<<"\n";



            if(hero.wybranaBron->reloadClock.getElapsedTime().asSeconds()>hero.wybranaBron->reloadTime)
            {
            p8 << "READY!/" << std::fixed << std::setprecision(2)<<hero.wybranaBron->reloadTime;
            }
            else{
            p8 << std::fixed<<std::setprecision(2)<<hero.wybranaBron->reloadClock.getElapsedTime().asSeconds()<<"/" << std::fixed << std::setprecision(2)<<hero.wybranaBron->reloadTime;
            }
            
        infoTESR.text.setString(p1.str()+=p2.str()+=p3.str()+=p4.str()+=p5.str()+=p6.str()+=p7.str()+=p8.str());
            Animacje.hand(hero,hCLOCK,5);
            Animacje.runAnimation(enemyNO1, enemyClock, 4);
            Animacje.runAnimation(itemNO1, animateCLOCK,4);
            
            
        }else if(wygrana){
            GameOverBlok.text.setString("WIN!");
            GameOverBlok.setPosAuto(heroView.view, XPos::Center, YPos::Middle);
            GameOverBlok.setSizeAll(heroView.zoomFactor);
            GameOverBlok.text.setPosition(
            GameOverBlok.rectangle.getPosition().x+GameOverBlok.rectangle.getGlobalBounds().width/2-GameOverBlok.text.getGlobalBounds().width/2,
            GameOverBlok.rectangle.getPosition().y+GameOverBlok.rectangle.getGlobalBounds().height/2-GameOverBlok.text.getGlobalBounds().height/2);
        }else{
            GameOverBlok.setPosAuto(heroView.view, XPos::Center, YPos::Middle);
            GameOverBlok.setSizeAll(heroView.zoomFactor);
            GameOverBlok.text.setPosition(
            GameOverBlok.rectangle.getPosition().x+GameOverBlok.rectangle.getGlobalBounds().width/2-GameOverBlok.text.getGlobalBounds().width/2,
            GameOverBlok.rectangle.getPosition().y+GameOverBlok.rectangle.getGlobalBounds().height/2-GameOverBlok.text.getGlobalBounds().height/2);
        }

        ///DRAW
//        sf::Color(60,80,245)
        window.clear(sf::Color(36,46,53,100));
        
        if(renderViewScope(heroView.view, BlokInformacyjny.rectangle)){BlokInformacyjny.draw(window);};
        
        for(auto &blok :blokiNO1){
            if(renderViewScope(heroView.view, blok)){
                blok.draw(window, colisionData);
            }
        }
        for(auto &spb :specialneBlokiNO1){
            if(renderViewScope(heroView.view, spb)){
                spb.draw(window,colisionData);
            }
        }
        for(auto &item :itemNO1){
            if(renderViewScope(heroView.view, item)){
                item.draw(window, colisionData);
            }
        }
        for(auto &enemy :enemyNO1){
            if(renderViewScope(heroView.view, enemy)){
                enemy.draw(window,colisionData,metaData);
            }

        }
        if(toggleforkeyB){
        for(auto &slot: slotyNO1){
            slot.draw(window);
        }
        for(auto &slotVal: slotsValNO1){
            window.draw(slotVal);
        }
        }
        
        hero.draw(window,colisionData);
        
        for(auto &bron :hero.bronie){
            if(bron.uzywana||toggleforkeyB){
            bron.draw(window, colisionData);
            }
        }
        

        infoTESR.draw(window);
        

        if( minimapON){
            RectForMinimap.draw(window);
        window.setView(minimapView);
            for(auto &blok :blokiNO1){
                if(renderViewScope(minimapView, blok)){
                    blok.draw(window, colisionData);
                }
            }
            for(auto &spb :specialneBlokiNO1){
                if(renderViewScope(minimapView, spb)){
                    spb.draw(window,colisionData);
                }
            }
            for(auto &item :itemNO1){
                if(renderViewScope(minimapView, item)){
                    item.draw(window, colisionData);
                }
            }
            for(auto &enemy :enemyNO1){
                if(renderViewScope(minimapView, enemy)){
                    enemy.draw(window,colisionData,metaData);
                }
            }

        hero.draw(window,false);
        }

        window.setView(heroView.view);
        if(hero.health<=0||wygrana){
        GameOverBlok.draw(window);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
