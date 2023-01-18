#include <Arduino.h>
#include "Flash.h"
#include "nvs_flash.h"  

void WriteFlash(String dado, String key)
{
    nvs_handle handler_particao_nvs;
    esp_err_t err;
    
    err = nvs_flash_init_partition("nvs");
     
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao iniciar partição NVS.");           
        return;
    }
 
    err = nvs_open_from_partition("nvs", "ns_nvs", NVS_READWRITE, &handler_particao_nvs);
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao abrir NVS como escrita/leitura"); 
        return;
    }

    char _dado [dado.length()];
    dado.toCharArray(_dado,dado.length()+3);

    char _key [key.length()];
    key.toCharArray(_key,key.length());

    Serial.println(_dado);
    
    /* Atualiza valor dentro da memoria flash */
    err = nvs_set_str(handler_particao_nvs, _key, _dado);
 
    if (err != ESP_OK)
    {
        //Serial.println("[ERRO] Erro ao gravar horimetro");                   
        nvs_close(handler_particao_nvs);
        return;
    }
    else
    {
        //Serial.println("Dado gravado com sucesso!");     
        nvs_commit(handler_particao_nvs);    
        nvs_close(handler_particao_nvs);      
    }
}


String ReadFlash(String key)
{
    nvs_handle handler_particao_nvs;
    esp_err_t err;

    char _key [15];
    key.toCharArray(_key,key.length());
     
    err = nvs_flash_init_partition("nvs");
     
    if (err != ESP_OK)
    {
        //Serial.println("[ERRO] Falha ao iniciar partição NVS.");         
        return "fail";
    }
 
    err = nvs_open_from_partition("nvs", "ns_nvs", NVS_READWRITE, &handler_particao_nvs);
    if (err != ESP_OK)
    {
        //Serial.println("[ERRO] Falha ao abrir NVS como escrita/leitura");         
        return "fail";
    }

    char dado_lido[20];
    size_t required_size=20;
    /* Faz a leitura do dado associado a chave definida em CHAVE_NVS */
    err = nvs_get_str(handler_particao_nvs, _key, dado_lido, &required_size);
   
    if (err != ESP_OK)
    {
        //Serial.println("[ERRO] Falha ao fazer leitura do dado");         
        return "fail";
    }
    else
    {
        //Serial.println("Dado lido com sucesso!");  
        nvs_close(handler_particao_nvs);   
        return dado_lido;
    }
}