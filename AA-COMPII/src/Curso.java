import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;

//import java.util.ArrayList;

public class Curso implements Serializable{

	private String nome;
	private String codigoCurso;
	private String departamento; //criar metodo construtor para Departamento
	//permitir criacao de novos cursos
	
	//private ArrayList<Aluno> alunos;
	
	static Object [][] array = { {"","",""} };

	ArrayList<Object> dadosCurso = new ArrayList<Object>(Arrays.asList(array));

	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getCodigoCurso() {
		return codigoCurso;
	}
	public void setCodigoCurso(String codigoCurso) {
		this.codigoCurso = codigoCurso;
	}
	public String getDepartamento() {
		return departamento;
	}
	public void setDepartamento(String object) {
		this.departamento = object;
	}
	
	public boolean validaCodigoCurso(){
		boolean resultado = false;
		
		
		return resultado;
	}
	public Curso(){
		
	}
	
	public Curso(String nome, String codigo, String dept){
		this.setNome(nome);
		this.setCodigoCurso(codigo);
		this.setDepartamento(dept);
	}
	
}
