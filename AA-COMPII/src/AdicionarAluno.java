import java.awt.EventQueue;
import java.awt.Window;

import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JFormattedTextField;
import javax.swing.JRadioButton;
import javax.swing.JButton;

import java.awt.Font;

import javax.swing.JComboBox;
import javax.swing.table.DefaultTableModel;
import javax.swing.text.MaskFormatter;

import java.awt.Color;


public class AdicionarAluno {

	public JFrame frame;
	private JTextField nome;
	private JFormattedTextField anoIngresso;
	private JFormattedTextField matricula;
	final JRadioButton rMasc = new JRadioButton("Masculino");
	final JRadioButton rFem = new JRadioButton("Feminino");
	public static JComboBox comboBox;	
	JFormattedTextField cpf;
	JRadioButton rdbtnEspecializacao,rdbtnMestrado,rdbtnDoutorado;

	public AdicionarAluno() {
		
		frame = new JFrame();
		frame.setBounds(300, 100, 800, 600);
		frame.setTitle("Adicionar Aluno");
		frame.setResizable(false);
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.NORTH);
		
		JPanel panel_1 = new JPanel();
		frame.getContentPane().add(panel_1, BorderLayout.CENTER);
		panel_1.setLayout(null);
		
		JLabel lblNome = new JLabel("Nome:");
		lblNome.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblNome.setBounds(48, 81, 103, 14);
		panel_1.add(lblNome);
		
		nome = new JTextField();
		nome.setBounds(98, 80, 497, 20);
		panel_1.add(nome);
		nome.setColumns(10);
		
		JLabel lblMatrcula = new JLabel("Matr\u00EDcula:");
		lblMatrcula.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblMatrcula.setBounds(48, 132, 71, 14);
		panel_1.add(lblMatrcula);
		
		try{  
			  
	           MaskFormatter format_matricula = new MaskFormatter("#########-#"); 	  
	           matricula = new JFormattedTextField(format_matricula);  
	           matricula.setBounds(115, 131, 120, 20);
	   		   panel_1.add(matricula);
	           
	        }catch (Exception e){
	        	
	        }
		
		JLabel lblAnoDeIngresso = new JLabel("Ano de Ingresso:");
		lblAnoDeIngresso.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblAnoDeIngresso.setBounds(48, 180, 114, 19);
		panel_1.add(lblAnoDeIngresso);
		

		
		try{
			
			MaskFormatter format_ano = new MaskFormatter("####");
			anoIngresso = new JFormattedTextField(format_ano);
			anoIngresso.setBounds(159, 179, 71, 20);
			panel_1.add(anoIngresso);
		
		}catch(Exception e){
			
		}
		 
		
		JLabel lblCurso = new JLabel("Curso:");
		lblCurso.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblCurso.setBounds(48, 220, 71, 22);
		panel_1.add(lblCurso);
		
		JLabel lblCpf = new JLabel("CPF:");
		lblCpf.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblCpf.setBounds(48, 272, 71, 25);
		panel_1.add(lblCpf);
		
//		cpf = new JFormattedTextField();
	//	cpf.setBounds(98, 274, 137, 23);
//		panel_1.add(cpf);
	   
	       try{  
	  
	           MaskFormatter format_cpf = new MaskFormatter("###########");    
	           cpf = new JFormattedTextField(format_cpf);  
	           cpf.setBounds(98, 274, 137, 23);
	           panel_1.add(cpf);   
	        }catch (Exception e){
	        	
	        }
		
		
		ButtonGroup sexo = new ButtonGroup();
		ButtonGroup titulo = new ButtonGroup();
		
		
		rMasc.setFont(new Font("Tahoma", Font.BOLD, 12));
		rMasc.setBounds(48, 359, 109, 23);
		panel_1.add(rMasc);
		sexo.add(rMasc);
		

		rFem.setFont(new Font("Tahoma", Font.BOLD, 12));
		rFem.setBounds(48, 396, 109, 23);
		panel_1.add(rFem);
		sexo.add(rFem);
		
		JLabel lblSexo = new JLabel("Sexo:");
		lblSexo.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblSexo.setBounds(48, 334, 46, 14);
		panel_1.add(lblSexo);
		
		JButton bOK = new JButton("Criar");
		bOK.setBounds(340, 517, 89, 23);
		panel_1.add(bOK);
		
		rdbtnEspecializacao = new JRadioButton("Especializa\u00E7\u00E3o");
		rdbtnEspecializacao.setFont(new Font("Tahoma", Font.BOLD, 12));
		rdbtnEspecializacao.setBounds(351, 359, 109, 23);
		panel_1.add(rdbtnEspecializacao);
		titulo.add(rdbtnEspecializacao);
		
		JLabel lblTtulo = new JLabel("T\u00EDtulo:");
		lblTtulo.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblTtulo.setBounds(350, 334, 46, 14);
		panel_1.add(lblTtulo);
		
		
		rdbtnMestrado = new JRadioButton("Mestrado");
		rdbtnMestrado.setFont(new Font("Tahoma", Font.BOLD, 12));
		rdbtnMestrado.setBounds(351, 396, 109, 23);
		panel_1.add(rdbtnMestrado);
		titulo.add(rdbtnMestrado);
		
		rdbtnDoutorado = new JRadioButton("Doutorado");
		rdbtnDoutorado.setFont(new Font("Tahoma", Font.BOLD, 12));
		rdbtnDoutorado.setBounds(351, 439, 109, 23);
		panel_1.add(rdbtnDoutorado);
		titulo.add(rdbtnDoutorado);
		
		String [] listaCursos = new String[TelaPrincipal.db.getCurso().size()];
		
		for (int i = 0; i < TelaPrincipal.db.getCurso().size(); i++) {
			listaCursos[i] = TelaPrincipal.db.getCurso().get(i).getNome();			
		}
		
		comboBox = new JComboBox(listaCursos);
		comboBox.setBounds(98, 222, 230, 20);
		panel_1.add(comboBox);		
		
		JLabel lblAdicionandoAluno = new JLabel("Adicionar Aluno");
		lblAdicionandoAluno.setFont(new Font("Tahoma", Font.PLAIN, 20));
		lblAdicionandoAluno.setBounds(302, 21, 145, 23);
		panel_1.add(lblAdicionandoAluno);
		
		bOK.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				addAluno();
			}
		});
		
		
		
	}
	
	public void addAluno(){
			try{
			Aluno novoAluno = new Aluno(nome.getText(),matricula.getText(),anoIngresso.getText(),cpf.getText(),comboBox.getSelectedItem().toString());
			if(Aluno.validadeCPF(cpf.getText()) == true){
				
				novoAluno.setCPF(cpf.getText());
				novoAluno.setNome(nome.getText());
				novoAluno.setMatricula(matricula.getText());
				novoAluno.setAnoIngresso(anoIngresso.getText());
				if (rMasc.isSelected()){
					novoAluno.setSexo(Sexo.MASCULINO);
					}else{
					novoAluno.setSexo(Sexo.FEMININO);
					}
				if(rdbtnEspecializacao.isSelected()){
					novoAluno.setTitulo(Titulo.ESPECIALIZACAO);
				}
				else if(rdbtnMestrado.isSelected()){
					novoAluno.setTitulo(Titulo.MESTRADO);
				}else{
					novoAluno.setTitulo(Titulo.DOUTORADO);
				}
				TelaPrincipal.db.getAlunos().add(novoAluno);
				TelaPrincipal.tabela.preenche();
				frame.dispose();
			}
			else{
				JOptionPane.showMessageDialog(frame, "CPF inválido", "Erro", JOptionPane.ERROR_MESSAGE);
			}			
		}catch(Exception e){
				JOptionPane.showMessageDialog(frame, "Ainda há Campos em Branco", "Erro", JOptionPane.ERROR_MESSAGE);
		}
	}
}
