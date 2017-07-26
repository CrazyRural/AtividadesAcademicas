import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.text.MaskFormatter;


public class AtualizarDados {

	public JFrame frame;
	private JTextField nome;
	private JFormattedTextField anoIngresso;
	private JFormattedTextField matricula;
	final JRadioButton rMasc = new JRadioButton("Masculino");
	final JRadioButton rFem = new JRadioButton("Feminino");

	public AtualizarDados() {
		
		frame = new JFrame();
		frame.setBounds(300, 100, 800, 600);
		frame.setTitle("Atualizar Aluno");
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
		
//		cpf = new JFormattedTextField();
	//	cpf.setBounds(98, 274, 137, 23);
//		panel_1.add(cpf);
	   
	       try{  
	  
	           MaskFormatter format_cpf = new MaskFormatter("###########");
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
		
		JButton bOK = new JButton("Atualizar");
		bOK.setBounds(340, 517, 89, 23);
		panel_1.add(bOK);
		
		String [] listaCursos = new String[TelaPrincipal.db.getCurso().size()];
		
		for (int i = 0; i < TelaPrincipal.db.getCurso().size(); i++) {
			listaCursos[i] = TelaPrincipal.db.getCurso().get(i).getNome();			
		}
		
		JLabel lblAdicionandoAluno = new JLabel("Atualizar Aluno");
		lblAdicionandoAluno.setFont(new Font("Tahoma", Font.PLAIN, 20));
		lblAdicionandoAluno.setBounds(302, 21, 145, 23);
		panel_1.add(lblAdicionandoAluno);
		
		bOK.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				atAluno();
			}
		});
		
	
		nome.setText(TelaPrincipal.db.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).getNome());	
		matricula.setText(TelaPrincipal.db.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).getMatricula());
		anoIngresso.setText(TelaPrincipal.db.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).getAnoIngresso());
//		cpf.setText(DataBase.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).getCPF());
		
		
	}
	
	public void atAluno(){

		TelaPrincipal.db.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).setNome(nome.getText());
		TelaPrincipal.db.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).setMatricula(matricula.getText());
		TelaPrincipal.db.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).setAnoIngresso(anoIngresso.getText());
	//	DataBase.getAlunos().get(TelaPrincipal.tabela.getSelectedRow()).setCPF(cpf.getText());
		
		TelaPrincipal.tabela.preencheVazio();
		TelaPrincipal.tabela.preenche();
		
		frame.setVisible(false);
	}


}
