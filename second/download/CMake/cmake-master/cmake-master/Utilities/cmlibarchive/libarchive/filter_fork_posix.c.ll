; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/filter_fork_posix.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.posix_spawn_file_actions_t = type { i32, i32, %struct.__spawn_action*, [16 x i32] }
%struct.__spawn_action = type opaque
%struct.archive_cmdline = type { i8*, i8**, i32 }
%struct.posix_spawnattr_t = type { i16, i32, %struct.__sigset_t, %struct.__sigset_t, %struct.sched_param, i32, [16 x i32] }
%struct.__sigset_t = type { [16 x i64] }
%struct.sched_param = type { i32 }
%struct.pollfd = type { i32, i16, i16 }

; Function Attrs: nounwind uwtable
define i32 @__archive_create_child(i8* %cmd, i32* %child_stdin, i32* %child_stdout) #0 !dbg !6 {
entry:
  %retval = alloca i32, align 4
  %cmd.addr = alloca i8*, align 8
  %child_stdin.addr = alloca i32*, align 8
  %child_stdout.addr = alloca i32*, align 8
  %child = alloca i32, align 4
  %stdin_pipe = alloca [2 x i32], align 4
  %stdout_pipe = alloca [2 x i32], align 4
  %tmp = alloca i32, align 4
  %actions = alloca %struct.posix_spawn_file_actions_t, align 8
  %r = alloca i32, align 4
  %cmdline = alloca %struct.archive_cmdline*, align 8
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !24, metadata !25), !dbg !26
  store i32* %child_stdin, i32** %child_stdin.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %child_stdin.addr, metadata !27, metadata !25), !dbg !28
  store i32* %child_stdout, i32** %child_stdout.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %child_stdout.addr, metadata !29, metadata !25), !dbg !30
  call void @llvm.dbg.declare(metadata i32* %child, metadata !31, metadata !25), !dbg !32
  call void @llvm.dbg.declare(metadata [2 x i32]* %stdin_pipe, metadata !33, metadata !25), !dbg !37
  call void @llvm.dbg.declare(metadata [2 x i32]* %stdout_pipe, metadata !38, metadata !25), !dbg !39
  call void @llvm.dbg.declare(metadata i32* %tmp, metadata !40, metadata !25), !dbg !41
  call void @llvm.dbg.declare(metadata %struct.posix_spawn_file_actions_t* %actions, metadata !42, metadata !25), !dbg !56
  call void @llvm.dbg.declare(metadata i32* %r, metadata !57, metadata !25), !dbg !58
  call void @llvm.dbg.declare(metadata %struct.archive_cmdline** %cmdline, metadata !59, metadata !25), !dbg !69
  %call = call %struct.archive_cmdline* @__archive_cmdline_allocate(), !dbg !70
  store %struct.archive_cmdline* %call, %struct.archive_cmdline** %cmdline, align 8, !dbg !71
  %0 = load %struct.archive_cmdline*, %struct.archive_cmdline** %cmdline, align 8, !dbg !72
  %cmp = icmp eq %struct.archive_cmdline* %0, null, !dbg !74
  br i1 %cmp, label %if.then, label %if.end, !dbg !75

if.then:                                          ; preds = %entry
  br label %state_allocated, !dbg !76

if.end:                                           ; preds = %entry
  %1 = load %struct.archive_cmdline*, %struct.archive_cmdline** %cmdline, align 8, !dbg !77
  %2 = load i8*, i8** %cmd.addr, align 8, !dbg !79
  %call4 = call i32 @__archive_cmdline_parse(%struct.archive_cmdline* %1, i8* %2), !dbg !80
  %cmp5 = icmp ne i32 %call4, 0, !dbg !81
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !82

if.then6:                                         ; preds = %if.end
  br label %state_allocated, !dbg !83

if.end7:                                          ; preds = %if.end
  %arraydecay = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i32 0, i32 0, !dbg !84
  %call8 = call i32 @pipe(i32* %arraydecay) #5, !dbg !86
  %cmp9 = icmp eq i32 %call8, -1, !dbg !87
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !88

if.then10:                                        ; preds = %if.end7
  br label %state_allocated, !dbg !89

if.end11:                                         ; preds = %if.end7
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !90
  %3 = load i32, i32* %arrayidx, align 4, !dbg !90
  %cmp12 = icmp eq i32 %3, 1, !dbg !92
  br i1 %cmp12, label %if.then13, label %if.end22, !dbg !93

if.then13:                                        ; preds = %if.end11
  %arrayidx14 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !94
  %4 = load i32, i32* %arrayidx14, align 4, !dbg !94
  %call15 = call i32 @dup(i32 %4) #5, !dbg !97
  store i32 %call15, i32* %tmp, align 4, !dbg !98
  %cmp16 = icmp eq i32 %call15, -1, !dbg !99
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !100

if.then17:                                        ; preds = %if.then13
  br label %stdin_opened, !dbg !101

if.end18:                                         ; preds = %if.then13
  %arrayidx19 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !102
  %5 = load i32, i32* %arrayidx19, align 4, !dbg !102
  %call20 = call i32 @close(i32 %5), !dbg !103
  %6 = load i32, i32* %tmp, align 4, !dbg !104
  %arrayidx21 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !105
  store i32 %6, i32* %arrayidx21, align 4, !dbg !106
  br label %if.end22, !dbg !107

if.end22:                                         ; preds = %if.end18, %if.end11
  %arraydecay23 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i32 0, i32 0, !dbg !108
  %call24 = call i32 @pipe(i32* %arraydecay23) #5, !dbg !110
  %cmp25 = icmp eq i32 %call24, -1, !dbg !111
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !112

if.then26:                                        ; preds = %if.end22
  br label %stdin_opened, !dbg !113

if.end27:                                         ; preds = %if.end22
  %arrayidx28 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !114
  %7 = load i32, i32* %arrayidx28, align 4, !dbg !114
  %cmp29 = icmp eq i32 %7, 0, !dbg !116
  br i1 %cmp29, label %if.then30, label %if.end39, !dbg !117

if.then30:                                        ; preds = %if.end27
  %arrayidx31 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !118
  %8 = load i32, i32* %arrayidx31, align 4, !dbg !118
  %call32 = call i32 @dup(i32 %8) #5, !dbg !121
  store i32 %call32, i32* %tmp, align 4, !dbg !122
  %cmp33 = icmp eq i32 %call32, -1, !dbg !123
  br i1 %cmp33, label %if.then34, label %if.end35, !dbg !124

if.then34:                                        ; preds = %if.then30
  br label %stdout_opened, !dbg !125

if.end35:                                         ; preds = %if.then30
  %arrayidx36 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !126
  %9 = load i32, i32* %arrayidx36, align 4, !dbg !126
  %call37 = call i32 @close(i32 %9), !dbg !127
  %10 = load i32, i32* %tmp, align 4, !dbg !128
  %arrayidx38 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !129
  store i32 %10, i32* %arrayidx38, align 4, !dbg !130
  br label %if.end39, !dbg !131

if.end39:                                         ; preds = %if.end35, %if.end27
  %call40 = call i32 @posix_spawn_file_actions_init(%struct.posix_spawn_file_actions_t* %actions) #5, !dbg !132
  store i32 %call40, i32* %r, align 4, !dbg !133
  %11 = load i32, i32* %r, align 4, !dbg !134
  %cmp41 = icmp ne i32 %11, 0, !dbg !136
  br i1 %cmp41, label %if.then42, label %if.end44, !dbg !137

if.then42:                                        ; preds = %if.end39
  %12 = load i32, i32* %r, align 4, !dbg !138
  %call43 = call i32* @__errno_location() #1, !dbg !140
  store i32 %12, i32* %call43, align 4, !dbg !141
  br label %stdout_opened, !dbg !142

if.end44:                                         ; preds = %if.end39
  %arrayidx45 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 1, !dbg !143
  %13 = load i32, i32* %arrayidx45, align 4, !dbg !143
  %call46 = call i32 @posix_spawn_file_actions_addclose(%struct.posix_spawn_file_actions_t* %actions, i32 %13) #5, !dbg !144
  store i32 %call46, i32* %r, align 4, !dbg !145
  %14 = load i32, i32* %r, align 4, !dbg !146
  %cmp47 = icmp ne i32 %14, 0, !dbg !148
  br i1 %cmp47, label %if.then48, label %if.end49, !dbg !149

if.then48:                                        ; preds = %if.end44
  br label %actions_inited, !dbg !150

if.end49:                                         ; preds = %if.end44
  %arrayidx50 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 0, !dbg !151
  %15 = load i32, i32* %arrayidx50, align 4, !dbg !151
  %call51 = call i32 @posix_spawn_file_actions_addclose(%struct.posix_spawn_file_actions_t* %actions, i32 %15) #5, !dbg !152
  store i32 %call51, i32* %r, align 4, !dbg !153
  %16 = load i32, i32* %r, align 4, !dbg !154
  %cmp52 = icmp ne i32 %16, 0, !dbg !156
  br i1 %cmp52, label %if.then53, label %if.end54, !dbg !157

if.then53:                                        ; preds = %if.end49
  br label %actions_inited, !dbg !158

if.end54:                                         ; preds = %if.end49
  %arrayidx55 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !159
  %17 = load i32, i32* %arrayidx55, align 4, !dbg !159
  %call56 = call i32 @posix_spawn_file_actions_adddup2(%struct.posix_spawn_file_actions_t* %actions, i32 %17, i32 0) #5, !dbg !160
  store i32 %call56, i32* %r, align 4, !dbg !161
  %18 = load i32, i32* %r, align 4, !dbg !162
  %cmp57 = icmp ne i32 %18, 0, !dbg !164
  br i1 %cmp57, label %if.then58, label %if.end59, !dbg !165

if.then58:                                        ; preds = %if.end54
  br label %actions_inited, !dbg !166

if.end59:                                         ; preds = %if.end54
  %arrayidx60 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !167
  %19 = load i32, i32* %arrayidx60, align 4, !dbg !167
  %cmp61 = icmp ne i32 %19, 0, !dbg !169
  br i1 %cmp61, label %if.then62, label %if.end68, !dbg !170

if.then62:                                        ; preds = %if.end59
  %arrayidx63 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !171
  %20 = load i32, i32* %arrayidx63, align 4, !dbg !171
  %call64 = call i32 @posix_spawn_file_actions_addclose(%struct.posix_spawn_file_actions_t* %actions, i32 %20) #5, !dbg !173
  store i32 %call64, i32* %r, align 4, !dbg !174
  %21 = load i32, i32* %r, align 4, !dbg !175
  %cmp65 = icmp ne i32 %21, 0, !dbg !177
  br i1 %cmp65, label %if.then66, label %if.end67, !dbg !178

if.then66:                                        ; preds = %if.then62
  br label %actions_inited, !dbg !179

if.end67:                                         ; preds = %if.then62
  br label %if.end68, !dbg !180

if.end68:                                         ; preds = %if.end67, %if.end59
  %arrayidx69 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !181
  %22 = load i32, i32* %arrayidx69, align 4, !dbg !181
  %call70 = call i32 @posix_spawn_file_actions_adddup2(%struct.posix_spawn_file_actions_t* %actions, i32 %22, i32 1) #5, !dbg !182
  store i32 %call70, i32* %r, align 4, !dbg !183
  %23 = load i32, i32* %r, align 4, !dbg !184
  %cmp71 = icmp ne i32 %23, 0, !dbg !186
  br i1 %cmp71, label %if.then72, label %if.end73, !dbg !187

if.then72:                                        ; preds = %if.end68
  br label %actions_inited, !dbg !188

if.end73:                                         ; preds = %if.end68
  %arrayidx74 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !189
  %24 = load i32, i32* %arrayidx74, align 4, !dbg !189
  %cmp75 = icmp ne i32 %24, 1, !dbg !191
  br i1 %cmp75, label %if.then76, label %if.end82, !dbg !192

if.then76:                                        ; preds = %if.end73
  %arrayidx77 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !193
  %25 = load i32, i32* %arrayidx77, align 4, !dbg !193
  %call78 = call i32 @posix_spawn_file_actions_addclose(%struct.posix_spawn_file_actions_t* %actions, i32 %25) #5, !dbg !195
  store i32 %call78, i32* %r, align 4, !dbg !196
  %26 = load i32, i32* %r, align 4, !dbg !197
  %cmp79 = icmp ne i32 %26, 0, !dbg !199
  br i1 %cmp79, label %if.then80, label %if.end81, !dbg !200

if.then80:                                        ; preds = %if.then76
  br label %actions_inited, !dbg !201

if.end81:                                         ; preds = %if.then76
  br label %if.end82, !dbg !202

if.end82:                                         ; preds = %if.end81, %if.end73
  %27 = load %struct.archive_cmdline*, %struct.archive_cmdline** %cmdline, align 8, !dbg !203
  %path = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %27, i32 0, i32 0, !dbg !204
  %28 = load i8*, i8** %path, align 8, !dbg !204
  %29 = load %struct.archive_cmdline*, %struct.archive_cmdline** %cmdline, align 8, !dbg !205
  %argv = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %29, i32 0, i32 1, !dbg !206
  %30 = load i8**, i8*** %argv, align 8, !dbg !206
  %call83 = call i32 @posix_spawnp(i32* %child, i8* %28, %struct.posix_spawn_file_actions_t* %actions, %struct.posix_spawnattr_t* null, i8** %30, i8** null), !dbg !207
  store i32 %call83, i32* %r, align 4, !dbg !208
  %31 = load i32, i32* %r, align 4, !dbg !209
  %cmp84 = icmp ne i32 %31, 0, !dbg !211
  br i1 %cmp84, label %if.then85, label %if.end86, !dbg !212

if.then85:                                        ; preds = %if.end82
  br label %actions_inited, !dbg !213

if.end86:                                         ; preds = %if.end82
  %call87 = call i32 @posix_spawn_file_actions_destroy(%struct.posix_spawn_file_actions_t* %actions) #5, !dbg !214
  %arrayidx88 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !215
  %32 = load i32, i32* %arrayidx88, align 4, !dbg !215
  %call89 = call i32 @close(i32 %32), !dbg !216
  %arrayidx90 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !217
  %33 = load i32, i32* %arrayidx90, align 4, !dbg !217
  %call91 = call i32 @close(i32 %33), !dbg !218
  %arrayidx92 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 1, !dbg !219
  %34 = load i32, i32* %arrayidx92, align 4, !dbg !219
  %35 = load i32*, i32** %child_stdin.addr, align 8, !dbg !220
  store i32 %34, i32* %35, align 4, !dbg !221
  %36 = load i32*, i32** %child_stdin.addr, align 8, !dbg !222
  %37 = load i32, i32* %36, align 4, !dbg !223
  %call93 = call i32 (i32, i32, ...) @fcntl(i32 %37, i32 4, i32 2048), !dbg !224
  %arrayidx94 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 0, !dbg !225
  %38 = load i32, i32* %arrayidx94, align 4, !dbg !225
  %39 = load i32*, i32** %child_stdout.addr, align 8, !dbg !226
  store i32 %38, i32* %39, align 4, !dbg !227
  %40 = load i32*, i32** %child_stdout.addr, align 8, !dbg !228
  %41 = load i32, i32* %40, align 4, !dbg !229
  %call95 = call i32 (i32, i32, ...) @fcntl(i32 %41, i32 4, i32 2048), !dbg !230
  %42 = load %struct.archive_cmdline*, %struct.archive_cmdline** %cmdline, align 8, !dbg !231
  %call96 = call i32 @__archive_cmdline_free(%struct.archive_cmdline* %42), !dbg !232
  %43 = load i32, i32* %child, align 4, !dbg !233
  store i32 %43, i32* %retval, align 4, !dbg !234
  br label %return, !dbg !234

actions_inited:                                   ; preds = %if.then85, %if.then80, %if.then72, %if.then66, %if.then58, %if.then53, %if.then48
  %44 = load i32, i32* %r, align 4, !dbg !235
  %call97 = call i32* @__errno_location() #1, !dbg !236
  store i32 %44, i32* %call97, align 4, !dbg !237
  %call98 = call i32 @posix_spawn_file_actions_destroy(%struct.posix_spawn_file_actions_t* %actions) #5, !dbg !238
  br label %stdout_opened, !dbg !238

stdout_opened:                                    ; preds = %actions_inited, %if.then42, %if.then34
  %arrayidx99 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 0, !dbg !239
  %45 = load i32, i32* %arrayidx99, align 4, !dbg !239
  %call100 = call i32 @close(i32 %45), !dbg !240
  %arrayidx101 = getelementptr inbounds [2 x i32], [2 x i32]* %stdout_pipe, i64 0, i64 1, !dbg !241
  %46 = load i32, i32* %arrayidx101, align 4, !dbg !241
  %call102 = call i32 @close(i32 %46), !dbg !242
  br label %stdin_opened, !dbg !242

stdin_opened:                                     ; preds = %stdout_opened, %if.then26, %if.then17
  %arrayidx103 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 0, !dbg !243
  %47 = load i32, i32* %arrayidx103, align 4, !dbg !243
  %call104 = call i32 @close(i32 %47), !dbg !244
  %arrayidx105 = getelementptr inbounds [2 x i32], [2 x i32]* %stdin_pipe, i64 0, i64 1, !dbg !245
  %48 = load i32, i32* %arrayidx105, align 4, !dbg !245
  %call106 = call i32 @close(i32 %48), !dbg !246
  br label %state_allocated, !dbg !246

state_allocated:                                  ; preds = %stdin_opened, %if.then10, %if.then6, %if.then
  %49 = load %struct.archive_cmdline*, %struct.archive_cmdline** %cmdline, align 8, !dbg !247
  %call107 = call i32 @__archive_cmdline_free(%struct.archive_cmdline* %49), !dbg !248
  store i32 -1, i32* %retval, align 4, !dbg !249
  br label %return, !dbg !249

return:                                           ; preds = %state_allocated, %if.end86
  %50 = load i32, i32* %retval, align 4, !dbg !250
  ret i32 %50, !dbg !250
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.archive_cmdline* @__archive_cmdline_allocate() #2

declare i32 @__archive_cmdline_parse(%struct.archive_cmdline*, i8*) #2

; Function Attrs: nounwind
declare i32 @pipe(i32*) #3

; Function Attrs: nounwind
declare i32 @dup(i32) #3

declare i32 @close(i32) #2

; Function Attrs: nounwind
declare i32 @posix_spawn_file_actions_init(%struct.posix_spawn_file_actions_t*) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind
declare i32 @posix_spawn_file_actions_addclose(%struct.posix_spawn_file_actions_t*, i32) #3

; Function Attrs: nounwind
declare i32 @posix_spawn_file_actions_adddup2(%struct.posix_spawn_file_actions_t*, i32, i32) #3

declare i32 @posix_spawnp(i32*, i8*, %struct.posix_spawn_file_actions_t*, %struct.posix_spawnattr_t*, i8**, i8**) #2

; Function Attrs: nounwind
declare i32 @posix_spawn_file_actions_destroy(%struct.posix_spawn_file_actions_t*) #3

declare i32 @fcntl(i32, i32, ...) #2

declare i32 @__archive_cmdline_free(%struct.archive_cmdline*) #2

; Function Attrs: nounwind uwtable
define void @__archive_check_child(i32 %in, i32 %out) #0 !dbg !18 {
entry:
  %in.addr = alloca i32, align 4
  %out.addr = alloca i32, align 4
  %fds = alloca [2 x %struct.pollfd], align 16
  %idx = alloca i32, align 4
  store i32 %in, i32* %in.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %in.addr, metadata !251, metadata !25), !dbg !252
  store i32 %out, i32* %out.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %out.addr, metadata !253, metadata !25), !dbg !254
  call void @llvm.dbg.declare(metadata [2 x %struct.pollfd]* %fds, metadata !255, metadata !25), !dbg !264
  call void @llvm.dbg.declare(metadata i32* %idx, metadata !265, metadata !25), !dbg !266
  store i32 0, i32* %idx, align 4, !dbg !267
  %0 = load i32, i32* %in.addr, align 4, !dbg !268
  %cmp = icmp ne i32 %0, -1, !dbg !270
  br i1 %cmp, label %if.then, label %if.end, !dbg !271

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %in.addr, align 4, !dbg !272
  %2 = load i32, i32* %idx, align 4, !dbg !274
  %idxprom = sext i32 %2 to i64, !dbg !275
  %arrayidx = getelementptr inbounds [2 x %struct.pollfd], [2 x %struct.pollfd]* %fds, i64 0, i64 %idxprom, !dbg !275
  %fd = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx, i32 0, i32 0, !dbg !276
  store i32 %1, i32* %fd, align 8, !dbg !277
  %3 = load i32, i32* %idx, align 4, !dbg !278
  %idxprom1 = sext i32 %3 to i64, !dbg !279
  %arrayidx2 = getelementptr inbounds [2 x %struct.pollfd], [2 x %struct.pollfd]* %fds, i64 0, i64 %idxprom1, !dbg !279
  %events = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx2, i32 0, i32 1, !dbg !280
  store i16 4, i16* %events, align 4, !dbg !281
  %4 = load i32, i32* %idx, align 4, !dbg !282
  %inc = add nsw i32 %4, 1, !dbg !282
  store i32 %inc, i32* %idx, align 4, !dbg !282
  br label %if.end, !dbg !283

if.end:                                           ; preds = %if.then, %entry
  %5 = load i32, i32* %out.addr, align 4, !dbg !284
  %cmp3 = icmp ne i32 %5, -1, !dbg !286
  br i1 %cmp3, label %if.then4, label %if.end12, !dbg !287

if.then4:                                         ; preds = %if.end
  %6 = load i32, i32* %out.addr, align 4, !dbg !288
  %7 = load i32, i32* %idx, align 4, !dbg !290
  %idxprom5 = sext i32 %7 to i64, !dbg !291
  %arrayidx6 = getelementptr inbounds [2 x %struct.pollfd], [2 x %struct.pollfd]* %fds, i64 0, i64 %idxprom5, !dbg !291
  %fd7 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx6, i32 0, i32 0, !dbg !292
  store i32 %6, i32* %fd7, align 8, !dbg !293
  %8 = load i32, i32* %idx, align 4, !dbg !294
  %idxprom8 = sext i32 %8 to i64, !dbg !295
  %arrayidx9 = getelementptr inbounds [2 x %struct.pollfd], [2 x %struct.pollfd]* %fds, i64 0, i64 %idxprom8, !dbg !295
  %events10 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx9, i32 0, i32 1, !dbg !296
  store i16 1, i16* %events10, align 4, !dbg !297
  %9 = load i32, i32* %idx, align 4, !dbg !298
  %inc11 = add nsw i32 %9, 1, !dbg !298
  store i32 %inc11, i32* %idx, align 4, !dbg !298
  br label %if.end12, !dbg !299

if.end12:                                         ; preds = %if.then4, %if.end
  %arraydecay = getelementptr inbounds [2 x %struct.pollfd], [2 x %struct.pollfd]* %fds, i32 0, i32 0, !dbg !300
  %10 = load i32, i32* %idx, align 4, !dbg !301
  %conv = sext i32 %10 to i64, !dbg !301
  %call = call i32 @poll(%struct.pollfd* %arraydecay, i64 %conv, i32 -1), !dbg !302
  ret void, !dbg !303
}

declare i32 @poll(%struct.pollfd*, i64, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!21, !22}
!llvm.ident = !{!23}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/filter_fork_posix.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !18}
!6 = distinct !DISubprogram(name: "__archive_create_child", scope: !1, file: !1, line: 76, type: !7, isLocal: false, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !14, !17, !17}
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !10, line: 98, baseType: !11)
!10 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !12, line: 133, baseType: !13)
!12 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!16 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!18 = distinct !DISubprogram(name: "__archive_check_child", scope: !1, file: !1, line: 199, type: !19, isLocal: false, isDefinition: true, scopeLine: 200, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{null, !13, !13}
!21 = !{i32 2, !"Dwarf Version", i32 4}
!22 = !{i32 2, !"Debug Info Version", i32 3}
!23 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!24 = !DILocalVariable(name: "cmd", arg: 1, scope: !6, file: !1, line: 76, type: !14)
!25 = !DIExpression()
!26 = !DILocation(line: 76, column: 36, scope: !6)
!27 = !DILocalVariable(name: "child_stdin", arg: 2, scope: !6, file: !1, line: 76, type: !17)
!28 = !DILocation(line: 76, column: 46, scope: !6)
!29 = !DILocalVariable(name: "child_stdout", arg: 3, scope: !6, file: !1, line: 76, type: !17)
!30 = !DILocation(line: 76, column: 64, scope: !6)
!31 = !DILocalVariable(name: "child", scope: !6, file: !1, line: 78, type: !9)
!32 = !DILocation(line: 78, column: 8, scope: !6)
!33 = !DILocalVariable(name: "stdin_pipe", scope: !6, file: !1, line: 79, type: !34)
!34 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 64, align: 32, elements: !35)
!35 = !{!36}
!36 = !DISubrange(count: 2)
!37 = !DILocation(line: 79, column: 6, scope: !6)
!38 = !DILocalVariable(name: "stdout_pipe", scope: !6, file: !1, line: 79, type: !34)
!39 = !DILocation(line: 79, column: 21, scope: !6)
!40 = !DILocalVariable(name: "tmp", scope: !6, file: !1, line: 79, type: !13)
!41 = !DILocation(line: 79, column: 37, scope: !6)
!42 = !DILocalVariable(name: "actions", scope: !6, file: !1, line: 81, type: !43)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "posix_spawn_file_actions_t", file: !44, line: 50, baseType: !45)
!44 = !DIFile(filename: "/usr/include/spawn.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DICompositeType(tag: DW_TAG_structure_type, file: !44, line: 44, size: 640, align: 64, elements: !46)
!46 = !{!47, !48, !49, !52}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "__allocated", scope: !45, file: !44, line: 46, baseType: !13, size: 32, align: 32)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "__used", scope: !45, file: !44, line: 47, baseType: !13, size: 32, align: 32, offset: 32)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "__actions", scope: !45, file: !44, line: 48, baseType: !50, size: 64, align: 64, offset: 64)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DICompositeType(tag: DW_TAG_structure_type, name: "__spawn_action", file: !44, line: 48, flags: DIFlagFwdDecl)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "__pad", scope: !45, file: !44, line: 49, baseType: !53, size: 512, align: 32, offset: 128)
!53 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 512, align: 32, elements: !54)
!54 = !{!55}
!55 = !DISubrange(count: 16)
!56 = !DILocation(line: 81, column: 29, scope: !6)
!57 = !DILocalVariable(name: "r", scope: !6, file: !1, line: 82, type: !13)
!58 = !DILocation(line: 82, column: 6, scope: !6)
!59 = !DILocalVariable(name: "cmdline", scope: !6, file: !1, line: 84, type: !60)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_cmdline", file: !62, line: 37, size: 192, align: 64, elements: !63)
!62 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cmdline_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!63 = !{!64, !66, !68}
!64 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !61, file: !62, line: 38, baseType: !65, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "argv", scope: !61, file: !62, line: 39, baseType: !67, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "argc", scope: !61, file: !62, line: 40, baseType: !13, size: 32, align: 32, offset: 128)
!69 = !DILocation(line: 84, column: 26, scope: !6)
!70 = !DILocation(line: 86, column: 12, scope: !6)
!71 = !DILocation(line: 86, column: 10, scope: !6)
!72 = !DILocation(line: 87, column: 6, scope: !73)
!73 = distinct !DILexicalBlock(scope: !6, file: !1, line: 87, column: 6)
!74 = !DILocation(line: 87, column: 14, scope: !73)
!75 = !DILocation(line: 87, column: 6, scope: !6)
!76 = !DILocation(line: 88, column: 3, scope: !73)
!77 = !DILocation(line: 89, column: 30, scope: !78)
!78 = distinct !DILexicalBlock(scope: !6, file: !1, line: 89, column: 6)
!79 = !DILocation(line: 89, column: 39, scope: !78)
!80 = !DILocation(line: 89, column: 6, scope: !78)
!81 = !DILocation(line: 89, column: 44, scope: !78)
!82 = !DILocation(line: 89, column: 6, scope: !6)
!83 = !DILocation(line: 90, column: 3, scope: !78)
!84 = !DILocation(line: 92, column: 11, scope: !85)
!85 = distinct !DILexicalBlock(scope: !6, file: !1, line: 92, column: 6)
!86 = !DILocation(line: 92, column: 6, scope: !85)
!87 = !DILocation(line: 92, column: 23, scope: !85)
!88 = !DILocation(line: 92, column: 6, scope: !6)
!89 = !DILocation(line: 93, column: 3, scope: !85)
!90 = !DILocation(line: 94, column: 6, scope: !91)
!91 = distinct !DILexicalBlock(scope: !6, file: !1, line: 94, column: 6)
!92 = !DILocation(line: 94, column: 20, scope: !91)
!93 = !DILocation(line: 94, column: 6, scope: !6)
!94 = !DILocation(line: 95, column: 18, scope: !95)
!95 = distinct !DILexicalBlock(scope: !96, file: !1, line: 95, column: 7)
!96 = distinct !DILexicalBlock(scope: !91, file: !1, line: 94, column: 39)
!97 = !DILocation(line: 95, column: 14, scope: !95)
!98 = !DILocation(line: 95, column: 12, scope: !95)
!99 = !DILocation(line: 95, column: 34, scope: !95)
!100 = !DILocation(line: 95, column: 7, scope: !96)
!101 = !DILocation(line: 96, column: 4, scope: !95)
!102 = !DILocation(line: 97, column: 9, scope: !96)
!103 = !DILocation(line: 97, column: 3, scope: !96)
!104 = !DILocation(line: 98, column: 19, scope: !96)
!105 = !DILocation(line: 98, column: 3, scope: !96)
!106 = !DILocation(line: 98, column: 17, scope: !96)
!107 = !DILocation(line: 99, column: 2, scope: !96)
!108 = !DILocation(line: 100, column: 11, scope: !109)
!109 = distinct !DILexicalBlock(scope: !6, file: !1, line: 100, column: 6)
!110 = !DILocation(line: 100, column: 6, scope: !109)
!111 = !DILocation(line: 100, column: 24, scope: !109)
!112 = !DILocation(line: 100, column: 6, scope: !6)
!113 = !DILocation(line: 101, column: 3, scope: !109)
!114 = !DILocation(line: 102, column: 6, scope: !115)
!115 = distinct !DILexicalBlock(scope: !6, file: !1, line: 102, column: 6)
!116 = !DILocation(line: 102, column: 21, scope: !115)
!117 = !DILocation(line: 102, column: 6, scope: !6)
!118 = !DILocation(line: 103, column: 18, scope: !119)
!119 = distinct !DILexicalBlock(scope: !120, file: !1, line: 103, column: 7)
!120 = distinct !DILexicalBlock(scope: !115, file: !1, line: 102, column: 39)
!121 = !DILocation(line: 103, column: 14, scope: !119)
!122 = !DILocation(line: 103, column: 12, scope: !119)
!123 = !DILocation(line: 103, column: 35, scope: !119)
!124 = !DILocation(line: 103, column: 7, scope: !120)
!125 = !DILocation(line: 104, column: 4, scope: !119)
!126 = !DILocation(line: 105, column: 9, scope: !120)
!127 = !DILocation(line: 105, column: 3, scope: !120)
!128 = !DILocation(line: 106, column: 20, scope: !120)
!129 = !DILocation(line: 106, column: 3, scope: !120)
!130 = !DILocation(line: 106, column: 18, scope: !120)
!131 = !DILocation(line: 107, column: 2, scope: !120)
!132 = !DILocation(line: 111, column: 6, scope: !6)
!133 = !DILocation(line: 111, column: 4, scope: !6)
!134 = !DILocation(line: 112, column: 6, scope: !135)
!135 = distinct !DILexicalBlock(scope: !6, file: !1, line: 112, column: 6)
!136 = !DILocation(line: 112, column: 8, scope: !135)
!137 = !DILocation(line: 112, column: 6, scope: !6)
!138 = !DILocation(line: 113, column: 11, scope: !139)
!139 = distinct !DILexicalBlock(scope: !135, file: !1, line: 112, column: 14)
!140 = !DILocation(line: 113, column: 3, scope: !139)
!141 = !DILocation(line: 113, column: 9, scope: !139)
!142 = !DILocation(line: 114, column: 3, scope: !139)
!143 = !DILocation(line: 116, column: 50, scope: !6)
!144 = !DILocation(line: 116, column: 6, scope: !6)
!145 = !DILocation(line: 116, column: 4, scope: !6)
!146 = !DILocation(line: 117, column: 6, scope: !147)
!147 = distinct !DILexicalBlock(scope: !6, file: !1, line: 117, column: 6)
!148 = !DILocation(line: 117, column: 8, scope: !147)
!149 = !DILocation(line: 117, column: 6, scope: !6)
!150 = !DILocation(line: 118, column: 3, scope: !147)
!151 = !DILocation(line: 119, column: 50, scope: !6)
!152 = !DILocation(line: 119, column: 6, scope: !6)
!153 = !DILocation(line: 119, column: 4, scope: !6)
!154 = !DILocation(line: 120, column: 6, scope: !155)
!155 = distinct !DILexicalBlock(scope: !6, file: !1, line: 120, column: 6)
!156 = !DILocation(line: 120, column: 8, scope: !155)
!157 = !DILocation(line: 120, column: 6, scope: !6)
!158 = !DILocation(line: 121, column: 3, scope: !155)
!159 = !DILocation(line: 123, column: 49, scope: !6)
!160 = !DILocation(line: 123, column: 6, scope: !6)
!161 = !DILocation(line: 123, column: 4, scope: !6)
!162 = !DILocation(line: 124, column: 6, scope: !163)
!163 = distinct !DILexicalBlock(scope: !6, file: !1, line: 124, column: 6)
!164 = !DILocation(line: 124, column: 8, scope: !163)
!165 = !DILocation(line: 124, column: 6, scope: !6)
!166 = !DILocation(line: 125, column: 3, scope: !163)
!167 = !DILocation(line: 126, column: 6, scope: !168)
!168 = distinct !DILexicalBlock(scope: !6, file: !1, line: 126, column: 6)
!169 = !DILocation(line: 126, column: 20, scope: !168)
!170 = !DILocation(line: 126, column: 6, scope: !6)
!171 = !DILocation(line: 127, column: 51, scope: !172)
!172 = distinct !DILexicalBlock(scope: !168, file: !1, line: 126, column: 38)
!173 = !DILocation(line: 127, column: 7, scope: !172)
!174 = !DILocation(line: 127, column: 5, scope: !172)
!175 = !DILocation(line: 128, column: 7, scope: !176)
!176 = distinct !DILexicalBlock(scope: !172, file: !1, line: 128, column: 7)
!177 = !DILocation(line: 128, column: 9, scope: !176)
!178 = !DILocation(line: 128, column: 7, scope: !172)
!179 = !DILocation(line: 129, column: 4, scope: !176)
!180 = !DILocation(line: 130, column: 2, scope: !172)
!181 = !DILocation(line: 132, column: 49, scope: !6)
!182 = !DILocation(line: 132, column: 6, scope: !6)
!183 = !DILocation(line: 132, column: 4, scope: !6)
!184 = !DILocation(line: 133, column: 6, scope: !185)
!185 = distinct !DILexicalBlock(scope: !6, file: !1, line: 133, column: 6)
!186 = !DILocation(line: 133, column: 8, scope: !185)
!187 = !DILocation(line: 133, column: 6, scope: !6)
!188 = !DILocation(line: 134, column: 3, scope: !185)
!189 = !DILocation(line: 135, column: 6, scope: !190)
!190 = distinct !DILexicalBlock(scope: !6, file: !1, line: 135, column: 6)
!191 = !DILocation(line: 135, column: 21, scope: !190)
!192 = !DILocation(line: 135, column: 6, scope: !6)
!193 = !DILocation(line: 136, column: 51, scope: !194)
!194 = distinct !DILexicalBlock(scope: !190, file: !1, line: 135, column: 40)
!195 = !DILocation(line: 136, column: 7, scope: !194)
!196 = !DILocation(line: 136, column: 5, scope: !194)
!197 = !DILocation(line: 137, column: 7, scope: !198)
!198 = distinct !DILexicalBlock(scope: !194, file: !1, line: 137, column: 7)
!199 = !DILocation(line: 137, column: 9, scope: !198)
!200 = !DILocation(line: 137, column: 7, scope: !194)
!201 = !DILocation(line: 138, column: 4, scope: !198)
!202 = !DILocation(line: 139, column: 2, scope: !194)
!203 = !DILocation(line: 140, column: 27, scope: !6)
!204 = !DILocation(line: 140, column: 36, scope: !6)
!205 = !DILocation(line: 141, column: 3, scope: !6)
!206 = !DILocation(line: 141, column: 12, scope: !6)
!207 = !DILocation(line: 140, column: 6, scope: !6)
!208 = !DILocation(line: 140, column: 4, scope: !6)
!209 = !DILocation(line: 142, column: 6, scope: !210)
!210 = distinct !DILexicalBlock(scope: !6, file: !1, line: 142, column: 6)
!211 = !DILocation(line: 142, column: 8, scope: !210)
!212 = !DILocation(line: 142, column: 6, scope: !6)
!213 = !DILocation(line: 143, column: 3, scope: !210)
!214 = !DILocation(line: 144, column: 2, scope: !6)
!215 = !DILocation(line: 171, column: 8, scope: !6)
!216 = !DILocation(line: 171, column: 2, scope: !6)
!217 = !DILocation(line: 172, column: 8, scope: !6)
!218 = !DILocation(line: 172, column: 2, scope: !6)
!219 = !DILocation(line: 174, column: 17, scope: !6)
!220 = !DILocation(line: 174, column: 3, scope: !6)
!221 = !DILocation(line: 174, column: 15, scope: !6)
!222 = !DILocation(line: 175, column: 9, scope: !6)
!223 = !DILocation(line: 175, column: 8, scope: !6)
!224 = !DILocation(line: 175, column: 2, scope: !6)
!225 = !DILocation(line: 176, column: 18, scope: !6)
!226 = !DILocation(line: 176, column: 3, scope: !6)
!227 = !DILocation(line: 176, column: 16, scope: !6)
!228 = !DILocation(line: 177, column: 9, scope: !6)
!229 = !DILocation(line: 177, column: 8, scope: !6)
!230 = !DILocation(line: 177, column: 2, scope: !6)
!231 = !DILocation(line: 178, column: 25, scope: !6)
!232 = !DILocation(line: 178, column: 2, scope: !6)
!233 = !DILocation(line: 180, column: 9, scope: !6)
!234 = !DILocation(line: 180, column: 2, scope: !6)
!235 = !DILocation(line: 184, column: 10, scope: !6)
!236 = !DILocation(line: 184, column: 2, scope: !6)
!237 = !DILocation(line: 184, column: 8, scope: !6)
!238 = !DILocation(line: 185, column: 2, scope: !6)
!239 = !DILocation(line: 188, column: 8, scope: !6)
!240 = !DILocation(line: 188, column: 2, scope: !6)
!241 = !DILocation(line: 189, column: 8, scope: !6)
!242 = !DILocation(line: 189, column: 2, scope: !6)
!243 = !DILocation(line: 191, column: 8, scope: !6)
!244 = !DILocation(line: 191, column: 2, scope: !6)
!245 = !DILocation(line: 192, column: 8, scope: !6)
!246 = !DILocation(line: 192, column: 2, scope: !6)
!247 = !DILocation(line: 194, column: 25, scope: !6)
!248 = !DILocation(line: 194, column: 2, scope: !6)
!249 = !DILocation(line: 195, column: 2, scope: !6)
!250 = !DILocation(line: 196, column: 1, scope: !6)
!251 = !DILocalVariable(name: "in", arg: 1, scope: !18, file: !1, line: 199, type: !13)
!252 = !DILocation(line: 199, column: 27, scope: !18)
!253 = !DILocalVariable(name: "out", arg: 2, scope: !18, file: !1, line: 199, type: !13)
!254 = !DILocation(line: 199, column: 35, scope: !18)
!255 = !DILocalVariable(name: "fds", scope: !18, file: !1, line: 202, type: !256)
!256 = !DICompositeType(tag: DW_TAG_array_type, baseType: !257, size: 128, align: 32, elements: !35)
!257 = !DICompositeType(tag: DW_TAG_structure_type, name: "pollfd", file: !258, line: 39, size: 64, align: 32, elements: !259)
!258 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/poll.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!259 = !{!260, !261, !263}
!260 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !257, file: !258, line: 41, baseType: !13, size: 32, align: 32)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !257, file: !258, line: 42, baseType: !262, size: 16, align: 16, offset: 32)
!262 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "revents", scope: !257, file: !258, line: 43, baseType: !262, size: 16, align: 16, offset: 48)
!264 = !DILocation(line: 202, column: 16, scope: !18)
!265 = !DILocalVariable(name: "idx", scope: !18, file: !1, line: 203, type: !13)
!266 = !DILocation(line: 203, column: 6, scope: !18)
!267 = !DILocation(line: 205, column: 6, scope: !18)
!268 = !DILocation(line: 206, column: 6, scope: !269)
!269 = distinct !DILexicalBlock(scope: !18, file: !1, line: 206, column: 6)
!270 = !DILocation(line: 206, column: 9, scope: !269)
!271 = !DILocation(line: 206, column: 6, scope: !18)
!272 = !DILocation(line: 207, column: 17, scope: !273)
!273 = distinct !DILexicalBlock(scope: !269, file: !1, line: 206, column: 16)
!274 = !DILocation(line: 207, column: 7, scope: !273)
!275 = !DILocation(line: 207, column: 3, scope: !273)
!276 = !DILocation(line: 207, column: 12, scope: !273)
!277 = !DILocation(line: 207, column: 15, scope: !273)
!278 = !DILocation(line: 208, column: 7, scope: !273)
!279 = !DILocation(line: 208, column: 3, scope: !273)
!280 = !DILocation(line: 208, column: 12, scope: !273)
!281 = !DILocation(line: 208, column: 19, scope: !273)
!282 = !DILocation(line: 209, column: 3, scope: !273)
!283 = !DILocation(line: 210, column: 2, scope: !273)
!284 = !DILocation(line: 211, column: 6, scope: !285)
!285 = distinct !DILexicalBlock(scope: !18, file: !1, line: 211, column: 6)
!286 = !DILocation(line: 211, column: 10, scope: !285)
!287 = !DILocation(line: 211, column: 6, scope: !18)
!288 = !DILocation(line: 212, column: 17, scope: !289)
!289 = distinct !DILexicalBlock(scope: !285, file: !1, line: 211, column: 17)
!290 = !DILocation(line: 212, column: 7, scope: !289)
!291 = !DILocation(line: 212, column: 3, scope: !289)
!292 = !DILocation(line: 212, column: 12, scope: !289)
!293 = !DILocation(line: 212, column: 15, scope: !289)
!294 = !DILocation(line: 213, column: 7, scope: !289)
!295 = !DILocation(line: 213, column: 3, scope: !289)
!296 = !DILocation(line: 213, column: 12, scope: !289)
!297 = !DILocation(line: 213, column: 19, scope: !289)
!298 = !DILocation(line: 214, column: 3, scope: !289)
!299 = !DILocation(line: 215, column: 2, scope: !289)
!300 = !DILocation(line: 217, column: 7, scope: !18)
!301 = !DILocation(line: 217, column: 12, scope: !18)
!302 = !DILocation(line: 217, column: 2, scope: !18)
!303 = !DILocation(line: 236, column: 1, scope: !18)
