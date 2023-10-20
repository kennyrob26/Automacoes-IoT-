var ativo = 0;

var conteudo = window.document.getElementById("opcoes_avancadas");
var botao = window.document.getElementById("abrir_opcoes_avancadas");

function clicou()
{
    if(ativo == 0)
    {
        conteudo.style.display = "block";

        ativo = 1;
    }
    else
    {
        conteudo.style.display = "none";
        ativo = 0;

    }
    
    
}