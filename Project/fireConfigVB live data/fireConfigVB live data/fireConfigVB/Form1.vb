Imports FireSharp.Config
Imports FireSharp.Response
Imports FireSharp.Interfaces
Imports Newtonsoft.Json
Imports System.Net
Imports System.IO

Public Class Form1

    Private fcon As New FirebaseConfig() With
        {
        .AuthSecret = "5DqxG7Wshfx0sSRoj3WOzJcSlRPdGLZimEtTuYi8",
        .BasePath = "https://flood-detector-c9726-default-rtdb.firebaseio.com"
        }

    Private client As IFirebaseClient

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Try
            client = New FireSharp.FirebaseClient(fcon)
        Catch
            MessageBox.Show("there was a problem with your internet")
        End Try

        LiveCall()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs)

    End Sub

    Private Async Sub LiveCall()
        While True
            Await Task.Delay(100)
            Dim res As FirebaseResponse = Await client.GetAsync("test")
            Dim data As Dictionary(Of String, String) = JsonConvert.DeserializeObject(Of Dictionary(Of String, String))(res.Body.ToString())
            UpdateRTB(data)
        End While
    End Sub

    Dim sec As Integer = 0
    Dim l As Integer = 1
    Private Sub UpdateRTB(ByVal records As Dictionary(Of String, String))
        Dim a As String

        a = records.ElementAt(0).Value & vbLf
        If (a = 2) Then

            If (l < 2) Then
                Shell("python main.py")

                l += 1
            End If
        End If
            If (a = 0) Then
            l = 1
        End If

    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs)

    End Sub
End Class