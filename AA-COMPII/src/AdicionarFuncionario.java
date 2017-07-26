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
import javax.swing.text.MaskFormatter;



	public class AdicionarFuncionario {
	
		JFrame frame;
		private JTextField nome;
		private JFormattedTextField anoIngresso;
		private JFormattedTextField CPF;
		public static JComboBox<?> comboBox;
		final JRadioButton rMasc;
		final JRadioButton rFem;
		JRadioButton rdbtnMestrado,rdbtnDoutorado,rdbtnEspecializacao;

		public AdicionarFuncionario() {

			frame = new JFrame();
			frame.setBounds(300, 100, 800, 600);
			frame.setTitle("Adicionar Funcionário");
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
			
			JLabel lblAnoDeIngresso = new JLabel("Ano de Ingresso:");
			lblAnoDeIngresso.setFont(new Font("Tahoma", Font.PLAIN, 14));
			lblAnoDeIngresso.setBounds(48, 180, 114, 19);
			panel_1.add(lblAnoDeIngresso);
			
			anoIngresso = new JFormattedTextField();
			anoIngresso.setBounds(159, 179, 71, 20);
			panel_1.add(anoIngresso);
			anoIngresso.setColumns(10);
			
			JLabel lblDepartamento = new JLabel("Departamento");
			lblDepartamento.setFont(new Font("Tahoma", Font.PLAIN, 14));
			lblDepartamento.setBounds(48, 220, 103, 22);
			panel_1.add(lblDepartamento);
			
			JLabel lblCpf = new JLabel("CPF:");
			lblCpf.setFont(new Font("Tahoma", Font.PLAIN, 14));
			lblCpf.setBounds(48, 130, 71, 25);
			panel_1.add(lblCpf);			
			
			try{  
				  
		           MaskFormatter format_cpf = new MaskFormatter("###########");    
		           CPF = new JFormattedTextField(format_cpf);  
		           CPF.setBounds(98, 133, 137, 23);
		           panel_1.add(CPF);   
		        }catch (Exception e){
		        	
		        }
			
			
			ButtonGroup sexo = new ButtonGroup();
			ButtonGroup titulo = new ButtonGroup();
			
			rMasc = new JRadioButton("Masculino");
			rMasc.setFont(new Font("Tahoma", Font.BOLD, 12));
			rMasc.setBounds(48, 303, 109, 23);
			panel_1.add(rMasc);
			sexo.add(rMasc);
			
			rFem = new JRadioButton("Feminino");
			rFem.setFont(new Font("Tahoma", Font.BOLD, 12));
			rFem.setBounds(48, 340, 109, 23);
			panel_1.add(rFem);
			sexo.add(rFem);
			
			JLabel lblSexo = new JLabel("Sexo:");
			lblSexo.setFont(new Font("Tahoma", Font.PLAIN, 14));
			lblSexo.setBounds(48, 278, 46, 14);
			panel_1.add(lblSexo);
			
			JButton bOK = new JButton("Criar");
			bOK.setBounds(340, 517, 89, 23);
			panel_1.add(bOK);
			
			rdbtnEspecializacao = new JRadioButton("Especializa\u00E7\u00E3o");
			rdbtnEspecializacao.setFont(new Font("Tahoma", Font.BOLD, 12));
			rdbtnEspecializacao.setBounds(351, 303, 109, 23);
			panel_1.add(rdbtnEspecializacao);
			titulo.add(rdbtnEspecializacao);
			
			JLabel lblTtulo = new JLabel("T\u00EDtulo:");
			lblTtulo.setFont(new Font("Tahoma", Font.PLAIN, 14));
			lblTtulo.setBounds(350, 278, 46, 14);
			panel_1.add(lblTtulo);
			
			
			rdbtnMestrado = new JRadioButton("Mestrado");
			rdbtnMestrado.setFont(new Font("Tahoma", Font.BOLD, 12));
			rdbtnMestrado.setBounds(351, 340, 109, 23);
			panel_1.add(rdbtnMestrado);
			titulo.add(rdbtnMestrado);
			
			rdbtnDoutorado = new JRadioButton("Doutorado");
			rdbtnDoutorado.setFont(new Font("Tahoma", Font.BOLD, 12));
			rdbtnDoutorado.setBounds(351, 383, 109, 23);
			panel_1.add(rdbtnDoutorado);
			titulo.add(rdbtnDoutorado);
			
			String [] listaDept = new String[TelaPrincipal.db.getDept().size()];
			
			for (int i = 0; i < TelaPrincipal.db.getDept().size(); i++) {
				listaDept[i] = TelaPrincipal.db.getDept().get(i).getNome();
				
			}
			
			comboBox = new JComboBox(listaDept);
			comboBox.setBounds(148, 223, 295, 20);
			panel_1.add(comboBox);			
			
			JLabel lblAdicionandoFuncionario = new JLabel("Adicionar Funcionario");
			lblAdicionandoFuncionario.setFont(new Font("Tahoma", Font.PLAIN, 20));
			lblAdicionandoFuncionario.setBounds(290, 22, 216, 23);
			panel_1.add(lblAdicionandoFuncionario);
			
			bOK.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					addFunc();
				}
			});			
		}
		
		public void addFunc(){
			try{
				Funcionario novofunc = new Funcionario(nome.getText(),anoIngresso.getText(),CPF.getText(),comboBox.getSelectedItem().toString());
				if(Funcionario.validadeCPF(CPF.getText()) == true){
					novofunc.setNome(nome.getText());
					novofunc.setAnoIngresso(anoIngresso.getText());
					novofunc.setCPF(CPF.getText());
					novofunc.setDepartamento(comboBox.getSelectedItem().toString());
					if (rMasc.isSelected()){
						novofunc.setSexo(Sexo.MASCULINO);
						}else{
						novofunc.setSexo(Sexo.FEMININO);
						}
					if(rdbtnEspecializacao.isSelected()){
						novofunc.setTitulo(Titulo.ESPECIALIZACAO);
					}
					else if(rdbtnMestrado.isSelected()){
						novofunc.setTitulo(Titulo.MESTRADO);
					}else{
						novofunc.setTitulo(Titulo.DOUTORADO);
					}
					TelaPrincipal.db.getFuncionario().add(novofunc);
					TelaPrincipal.tabela1.preenche();
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