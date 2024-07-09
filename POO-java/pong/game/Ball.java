import java.awt.*;
import java.util.*;
/**
	Esta classe representa a bola usada no jogo. A classe princial do jogo (Pong)
	instancia um objeto deste tipo quando a execução é iniciada.
*/

public class Ball {

	/**
		Construtor da classe Ball. Observe que quem invoca o construtor desta classe define a velocidade da bola 
		(em pixels por millisegundo), mas não define a direção deste movimento. A direção do movimento é determinada 
		aleatóriamente pelo construtor.

		@param cx coordenada x da posição inicial da bola (centro do retangulo que a representa).
		@param cy coordenada y da posição inicial da bola (centro do retangulo que a representa).
		@param width largura do retangulo que representa a bola.
		@param height altura do retangulo que representa a bola.
		@param color cor da bola.
		@param speed velocidade da bola (em pixels por millisegundo).
	*/

	double cx;
	double cy;
	double width;
	double height;
	Color color;
	double speed;
	double xSpeed;
	double ySpeed;

	Random movimentoAleatorio = new Random();

	public Ball(double cx, double cy, double width, double height, Color color, double speed){
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.speed = speed;

		int direcaoAleatoria1 = movimentoAleatorio.nextInt(2);
		double valorDaDirecao1 = (direcaoAleatoria1 == 0) ? -1:1; 
		this.xSpeed = speed*valorDaDirecao1;

		int direcaoAleatoria2 = movimentoAleatorio.nextInt(2);
		double valorDaDirecao2 = (direcaoAleatoria2 == 0) ? -1:1;
		this.ySpeed = speed*valorDaDirecao2;
	}


	/**
		Método chamado sempre que a bola precisa ser (re)desenhada.
	*/

	public void draw(){

		GameLib.setColor(color);
		GameLib.fillRect(cx, cy, width, height);
	}

	/**
		Método chamado quando o estado (posição) da bola precisa ser atualizado.
		
		@param delta quantidade de millisegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/

	public void update(long delta){
		cx += delta*xSpeed/1.5;
		cy += delta*ySpeed/1.5;
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com um jogador.
	
		@param playerId uma string cujo conteúdo identifica um dos jogadores.
	*/

	public void onPlayerCollision(String playerId){
		this.xSpeed = this.xSpeed*(-1);
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com uma parede.

		@param wallId uma string cujo conteúdo identifica uma das paredes da quadra.
	*/

	public void onWallCollision(String wallId){
		
		switch(wallId){
			case "Left":
			case "Right":
				this.xSpeed = this.xSpeed*(-1);
				this.speed = this.speed*(-1);
				break;

			case "Top":
			case "Bottom":
				this.ySpeed = this.ySpeed*(-1);
				this.speed = this.speed*(-1);
				break;

			default:
				break;
		}
	}

	/**
		Método que verifica se houve colisão da bola com uma parede.

		@param wall referência para uma instância de Wall contra a qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/
	
	public boolean checkCollision(Wall wall){
		switch (wall.getId()) {

			case "Left":
				if(wall.getCx() + wall.getWidth()/2 >= this.cx - this.width/2) return true;
				break;
			case "Right":
				if(wall.getCx() - wall.getWidth()/2 <= this.cx + this.width/2) return true;
				break;
			case "Top":
				if(wall.getCy() + wall.getHeight()/2 >= this.cy - this.height/2) return true;
				break;
			case "Bottom":
				if(wall.getCy() - wall.getHeight()/2 <= this.cy + this.height/2) return true;
				break;
			default:
				return false;
		}
		return false;
	}

	/**
		Método que verifica se houve colisão da bola com um jogador.

		@param player referência para uma instância de Player contra o qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/	

	public boolean checkCollision(Player player){

		if ( 
		(
		( (this.getCy() + this.height/2) <= (player.getCy() + player.getHeight()/2 +2) ) 
		&& 
		( (this.getCy() - this.height/2) >= (player.getCy() - player.getHeight()/2 -2)) 
		)
		 ) {
		
		if(player.getId() == "Player 1"){
			if( (
				this.getCx() - this.width/2 < player.getCx() + player.getWidth()/2)
				&& 
				(this.xSpeed < 0)
				&&
				// Evitar que um jogador rebata uma bola quase colidindo com a parede
				!(this.getCx() - this.width/2*(2/3) <= player.getCx() - player.getWidth()/2)
			){
				return true;
			}
		}
		if(player.getId() == "Player 2"){
			if( (this.getCx() + this.width/2 > player.getCx() - player.getWidth()/2)
				&&
				(this.xSpeed > 0)
				&&
				// Evitar que um jogador rebata uma bola quase colidindo com a parede
				!(this.getCx() + this.width/2*(2/3) >= player.getCx() + player.getWidth()/2)
			) {	
				return true;
			}
		}
		}

		return false;
	}

	/**
		Método que devolve a coordenada x do centro do retângulo que representa a bola.
		@return o valor double da coordenada x.
	*/
	
	public double getCx(){

		return this.cx;
	}

	/**
		Método que devolve a coordenada y do centro do retângulo que representa a bola.
		@return o valor double da coordenada y.
	*/

	public double getCy(){

		return this.cy;
	}

	/**
		Método que devolve a velocidade da bola.
		@return o valor double da velocidade.

	*/

	public double getSpeed(){

		return this.speed;
	}

}
