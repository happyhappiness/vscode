; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/System.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i8** @cmsysSystem_Parse_CommandForUnix(i8* %command, i32 %flags) #0 !dbg !29 {
entry:
  %retval = alloca i8**, align 8
  %command.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  store i8* %command, i8** %command.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %command.addr, metadata !47, metadata !48), !dbg !49
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !50, metadata !48), !dbg !51
  %0 = load i32, i32* %flags.addr, align 4, !dbg !52
  %cmp = icmp ne i32 %0, 0, !dbg !54
  br i1 %cmp, label %if.then, label %if.end, !dbg !55

if.then:                                          ; preds = %entry
  store i8** null, i8*** %retval, align 8, !dbg !56
  br label %return, !dbg !56

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %command.addr, align 8, !dbg !58
  %2 = load i32, i32* %flags.addr, align 4, !dbg !59
  %call = call i8** @kwsysSystem__ParseUnixCommand(i8* %1, i32 %2), !dbg !60
  store i8** %call, i8*** %retval, align 8, !dbg !61
  br label %return, !dbg !61

return:                                           ; preds = %if.end, %if.then
  %3 = load i8**, i8*** %retval, align 8, !dbg !62
  ret i8** %3, !dbg !62
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i8** @kwsysSystem__ParseUnixCommand(i8* %command, i32 %flags) #0 !dbg !35 {
entry:
  %command.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %local_pointers = alloca [32 x i8*], align 16
  %pointers_size = alloca i32, align 4
  %pointer_begin = alloca i8**, align 8
  %pointer_end = alloca i8**, align 8
  %local_buffer = alloca [1024 x i8], align 16
  %buffer_size = alloca i32, align 4
  %buffer_begin = alloca i8*, align 8
  %buffer_end = alloca i8*, align 8
  %newCommand = alloca i8**, align 8
  %c = alloca i8*, align 8
  %in_argument = alloca i32, align 4
  %in_escape = alloca i32, align 4
  %in_single = alloca i32, align 4
  %in_double = alloca i32, align 4
  %failed = alloca i32, align 4
  %n = alloca i64, align 8
  %n92 = alloca i64, align 8
  store i8* %command, i8** %command.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %command.addr, metadata !63, metadata !48), !dbg !64
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !65, metadata !48), !dbg !66
  call void @llvm.dbg.declare(metadata [32 x i8*]* %local_pointers, metadata !67, metadata !48), !dbg !71
  call void @llvm.dbg.declare(metadata i32* %pointers_size, metadata !72, metadata !48), !dbg !73
  store i32 32, i32* %pointers_size, align 4, !dbg !73
  call void @llvm.dbg.declare(metadata i8*** %pointer_begin, metadata !74, metadata !48), !dbg !75
  %arraydecay = getelementptr inbounds [32 x i8*], [32 x i8*]* %local_pointers, i32 0, i32 0, !dbg !76
  store i8** %arraydecay, i8*** %pointer_begin, align 8, !dbg !75
  call void @llvm.dbg.declare(metadata i8*** %pointer_end, metadata !77, metadata !48), !dbg !78
  %0 = load i8**, i8*** %pointer_begin, align 8, !dbg !79
  store i8** %0, i8*** %pointer_end, align 8, !dbg !78
  call void @llvm.dbg.declare(metadata [1024 x i8]* %local_buffer, metadata !80, metadata !48), !dbg !84
  call void @llvm.dbg.declare(metadata i32* %buffer_size, metadata !85, metadata !48), !dbg !86
  store i32 1024, i32* %buffer_size, align 4, !dbg !86
  call void @llvm.dbg.declare(metadata i8** %buffer_begin, metadata !87, metadata !48), !dbg !88
  %arraydecay1 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !89
  store i8* %arraydecay1, i8** %buffer_begin, align 8, !dbg !88
  call void @llvm.dbg.declare(metadata i8** %buffer_end, metadata !90, metadata !48), !dbg !91
  %1 = load i8*, i8** %buffer_begin, align 8, !dbg !92
  store i8* %1, i8** %buffer_end, align 8, !dbg !91
  call void @llvm.dbg.declare(metadata i8*** %newCommand, metadata !93, metadata !48), !dbg !94
  store i8** null, i8*** %newCommand, align 8, !dbg !94
  call void @llvm.dbg.declare(metadata i8** %c, metadata !95, metadata !48), !dbg !96
  %2 = load i8*, i8** %command.addr, align 8, !dbg !97
  store i8* %2, i8** %c, align 8, !dbg !96
  call void @llvm.dbg.declare(metadata i32* %in_argument, metadata !98, metadata !48), !dbg !99
  store i32 0, i32* %in_argument, align 4, !dbg !99
  call void @llvm.dbg.declare(metadata i32* %in_escape, metadata !100, metadata !48), !dbg !101
  store i32 0, i32* %in_escape, align 4, !dbg !101
  call void @llvm.dbg.declare(metadata i32* %in_single, metadata !102, metadata !48), !dbg !103
  store i32 0, i32* %in_single, align 4, !dbg !103
  call void @llvm.dbg.declare(metadata i32* %in_double, metadata !104, metadata !48), !dbg !105
  store i32 0, i32* %in_double, align 4, !dbg !105
  call void @llvm.dbg.declare(metadata i32* %failed, metadata !106, metadata !48), !dbg !107
  store i32 0, i32* %failed, align 4, !dbg !107
  br label %for.cond, !dbg !108

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i8*, i8** %c, align 8, !dbg !109
  %4 = load i8, i8* %3, align 1, !dbg !113
  %tobool = icmp ne i8 %4, 0, !dbg !114
  br i1 %tobool, label %for.body, label %for.end, !dbg !114

for.body:                                         ; preds = %for.cond
  %5 = load i32, i32* %in_escape, align 4, !dbg !115
  %tobool2 = icmp ne i32 %5, 0, !dbg !115
  br i1 %tobool2, label %if.then, label %if.else, !dbg !118

if.then:                                          ; preds = %for.body
  %6 = load i32, i32* %in_argument, align 4, !dbg !119
  %tobool3 = icmp ne i32 %6, 0, !dbg !119
  br i1 %tobool3, label %if.end, label %if.then4, !dbg !122

if.then4:                                         ; preds = %if.then
  store i32 1, i32* %in_argument, align 4, !dbg !123
  br label %if.end, !dbg !125

if.end:                                           ; preds = %if.then4, %if.then
  %arraydecay5 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !126
  %7 = load i8*, i8** %c, align 8, !dbg !128
  %8 = load i8, i8* %7, align 1, !dbg !129
  %call = call i32 @kwsysSystem__AppendByte(i8* %arraydecay5, i8** %buffer_begin, i8** %buffer_end, i32* %buffer_size, i8 signext %8), !dbg !130
  %tobool6 = icmp ne i32 %call, 0, !dbg !130
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !131

if.then7:                                         ; preds = %if.end
  store i32 1, i32* %failed, align 4, !dbg !132
  br label %for.end, !dbg !134

if.end8:                                          ; preds = %if.end
  store i32 0, i32* %in_escape, align 4, !dbg !135
  br label %if.end76, !dbg !136

if.else:                                          ; preds = %for.body
  %9 = load i8*, i8** %c, align 8, !dbg !137
  %10 = load i8, i8* %9, align 1, !dbg !140
  %conv = sext i8 %10 to i32, !dbg !140
  %cmp = icmp eq i32 %conv, 92, !dbg !141
  br i1 %cmp, label %if.then10, label %if.else11, !dbg !140

if.then10:                                        ; preds = %if.else
  store i32 1, i32* %in_escape, align 4, !dbg !142
  br label %if.end75, !dbg !144

if.else11:                                        ; preds = %if.else
  %11 = load i8*, i8** %c, align 8, !dbg !145
  %12 = load i8, i8* %11, align 1, !dbg !148
  %conv12 = sext i8 %12 to i32, !dbg !148
  %cmp13 = icmp eq i32 %conv12, 39, !dbg !149
  br i1 %cmp13, label %land.lhs.true, label %if.else24, !dbg !150

land.lhs.true:                                    ; preds = %if.else11
  %13 = load i32, i32* %in_double, align 4, !dbg !151
  %tobool15 = icmp ne i32 %13, 0, !dbg !151
  br i1 %tobool15, label %if.else24, label %if.then16, !dbg !153

if.then16:                                        ; preds = %land.lhs.true
  %14 = load i32, i32* %in_single, align 4, !dbg !154
  %tobool17 = icmp ne i32 %14, 0, !dbg !154
  br i1 %tobool17, label %if.then18, label %if.else19, !dbg !157

if.then18:                                        ; preds = %if.then16
  store i32 0, i32* %in_single, align 4, !dbg !158
  br label %if.end23, !dbg !160

if.else19:                                        ; preds = %if.then16
  store i32 1, i32* %in_single, align 4, !dbg !161
  %15 = load i32, i32* %in_argument, align 4, !dbg !163
  %tobool20 = icmp ne i32 %15, 0, !dbg !163
  br i1 %tobool20, label %if.end22, label %if.then21, !dbg !165

if.then21:                                        ; preds = %if.else19
  store i32 1, i32* %in_argument, align 4, !dbg !166
  br label %if.end22, !dbg !168

if.end22:                                         ; preds = %if.then21, %if.else19
  br label %if.end23

if.end23:                                         ; preds = %if.end22, %if.then18
  br label %if.end74, !dbg !169

if.else24:                                        ; preds = %land.lhs.true, %if.else11
  %16 = load i8*, i8** %c, align 8, !dbg !170
  %17 = load i8, i8* %16, align 1, !dbg !173
  %conv25 = sext i8 %17 to i32, !dbg !173
  %cmp26 = icmp eq i32 %conv25, 34, !dbg !174
  br i1 %cmp26, label %land.lhs.true28, label %if.else38, !dbg !175

land.lhs.true28:                                  ; preds = %if.else24
  %18 = load i32, i32* %in_single, align 4, !dbg !176
  %tobool29 = icmp ne i32 %18, 0, !dbg !176
  br i1 %tobool29, label %if.else38, label %if.then30, !dbg !178

if.then30:                                        ; preds = %land.lhs.true28
  %19 = load i32, i32* %in_double, align 4, !dbg !179
  %tobool31 = icmp ne i32 %19, 0, !dbg !179
  br i1 %tobool31, label %if.then32, label %if.else33, !dbg !182

if.then32:                                        ; preds = %if.then30
  store i32 0, i32* %in_double, align 4, !dbg !183
  br label %if.end37, !dbg !185

if.else33:                                        ; preds = %if.then30
  store i32 1, i32* %in_double, align 4, !dbg !186
  %20 = load i32, i32* %in_argument, align 4, !dbg !188
  %tobool34 = icmp ne i32 %20, 0, !dbg !188
  br i1 %tobool34, label %if.end36, label %if.then35, !dbg !190

if.then35:                                        ; preds = %if.else33
  store i32 1, i32* %in_argument, align 4, !dbg !191
  br label %if.end36, !dbg !193

if.end36:                                         ; preds = %if.then35, %if.else33
  br label %if.end37

if.end37:                                         ; preds = %if.end36, %if.then32
  br label %if.end73, !dbg !194

if.else38:                                        ; preds = %land.lhs.true28, %if.else24
  %21 = load i8*, i8** %c, align 8, !dbg !195
  %22 = load i8, i8* %21, align 1, !dbg !195
  %conv39 = zext i8 %22 to i32, !dbg !195
  %idxprom = sext i32 %conv39 to i64, !dbg !195
  %call40 = call i16** @__ctype_b_loc() #1, !dbg !195
  %23 = load i16*, i16** %call40, align 8, !dbg !195
  %arrayidx = getelementptr inbounds i16, i16* %23, i64 %idxprom, !dbg !195
  %24 = load i16, i16* %arrayidx, align 2, !dbg !195
  %conv41 = zext i16 %24 to i32, !dbg !195
  %and = and i32 %conv41, 8192, !dbg !195
  %tobool42 = icmp ne i32 %and, 0, !dbg !195
  br i1 %tobool42, label %if.then43, label %if.else63, !dbg !195

if.then43:                                        ; preds = %if.else38
  %25 = load i32, i32* %in_argument, align 4, !dbg !198
  %tobool44 = icmp ne i32 %25, 0, !dbg !198
  br i1 %tobool44, label %if.then45, label %if.end62, !dbg !201

if.then45:                                        ; preds = %if.then43
  %26 = load i32, i32* %in_single, align 4, !dbg !202
  %tobool46 = icmp ne i32 %26, 0, !dbg !202
  br i1 %tobool46, label %if.then48, label %lor.lhs.false, !dbg !205

lor.lhs.false:                                    ; preds = %if.then45
  %27 = load i32, i32* %in_double, align 4, !dbg !206
  %tobool47 = icmp ne i32 %27, 0, !dbg !206
  br i1 %tobool47, label %if.then48, label %if.else54, !dbg !208

if.then48:                                        ; preds = %lor.lhs.false, %if.then45
  %arraydecay49 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !209
  %28 = load i8*, i8** %c, align 8, !dbg !212
  %29 = load i8, i8* %28, align 1, !dbg !213
  %call50 = call i32 @kwsysSystem__AppendByte(i8* %arraydecay49, i8** %buffer_begin, i8** %buffer_end, i32* %buffer_size, i8 signext %29), !dbg !214
  %tobool51 = icmp ne i32 %call50, 0, !dbg !214
  br i1 %tobool51, label %if.end53, label %if.then52, !dbg !215

if.then52:                                        ; preds = %if.then48
  store i32 1, i32* %failed, align 4, !dbg !216
  br label %for.end, !dbg !218

if.end53:                                         ; preds = %if.then48
  br label %if.end61, !dbg !219

if.else54:                                        ; preds = %lor.lhs.false
  %arraydecay55 = getelementptr inbounds [32 x i8*], [32 x i8*]* %local_pointers, i32 0, i32 0, !dbg !220
  %arraydecay56 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !223
  %call57 = call i32 @kwsysSystem__AppendArgument(i8** %arraydecay55, i8*** %pointer_begin, i8*** %pointer_end, i32* %pointers_size, i8* %arraydecay56, i8** %buffer_begin, i8** %buffer_end, i32* %buffer_size), !dbg !224
  %tobool58 = icmp ne i32 %call57, 0, !dbg !224
  br i1 %tobool58, label %if.end60, label %if.then59, !dbg !225

if.then59:                                        ; preds = %if.else54
  store i32 1, i32* %failed, align 4, !dbg !226
  br label %for.end, !dbg !228

if.end60:                                         ; preds = %if.else54
  store i32 0, i32* %in_argument, align 4, !dbg !229
  br label %if.end61

if.end61:                                         ; preds = %if.end60, %if.end53
  br label %if.end62, !dbg !230

if.end62:                                         ; preds = %if.end61, %if.then43
  br label %if.end72, !dbg !231

if.else63:                                        ; preds = %if.else38
  %30 = load i32, i32* %in_argument, align 4, !dbg !232
  %tobool64 = icmp ne i32 %30, 0, !dbg !232
  br i1 %tobool64, label %if.end66, label %if.then65, !dbg !235

if.then65:                                        ; preds = %if.else63
  store i32 1, i32* %in_argument, align 4, !dbg !236
  br label %if.end66, !dbg !238

if.end66:                                         ; preds = %if.then65, %if.else63
  %arraydecay67 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !239
  %31 = load i8*, i8** %c, align 8, !dbg !241
  %32 = load i8, i8* %31, align 1, !dbg !242
  %call68 = call i32 @kwsysSystem__AppendByte(i8* %arraydecay67, i8** %buffer_begin, i8** %buffer_end, i32* %buffer_size, i8 signext %32), !dbg !243
  %tobool69 = icmp ne i32 %call68, 0, !dbg !243
  br i1 %tobool69, label %if.end71, label %if.then70, !dbg !244

if.then70:                                        ; preds = %if.end66
  store i32 1, i32* %failed, align 4, !dbg !245
  br label %for.end, !dbg !247

if.end71:                                         ; preds = %if.end66
  br label %if.end72

if.end72:                                         ; preds = %if.end71, %if.end62
  br label %if.end73

if.end73:                                         ; preds = %if.end72, %if.end37
  br label %if.end74

if.end74:                                         ; preds = %if.end73, %if.end23
  br label %if.end75

if.end75:                                         ; preds = %if.end74, %if.then10
  br label %if.end76

if.end76:                                         ; preds = %if.end75, %if.end8
  br label %for.inc, !dbg !248

for.inc:                                          ; preds = %if.end76
  %33 = load i8*, i8** %c, align 8, !dbg !249
  %incdec.ptr = getelementptr inbounds i8, i8* %33, i32 1, !dbg !249
  store i8* %incdec.ptr, i8** %c, align 8, !dbg !249
  br label %for.cond, !dbg !251

for.end:                                          ; preds = %if.then70, %if.then59, %if.then52, %if.then7, %for.cond
  %34 = load i32, i32* %in_argument, align 4, !dbg !252
  %tobool77 = icmp ne i32 %34, 0, !dbg !252
  br i1 %tobool77, label %if.then78, label %if.end85, !dbg !254

if.then78:                                        ; preds = %for.end
  %arraydecay79 = getelementptr inbounds [32 x i8*], [32 x i8*]* %local_pointers, i32 0, i32 0, !dbg !255
  %arraydecay80 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !258
  %call81 = call i32 @kwsysSystem__AppendArgument(i8** %arraydecay79, i8*** %pointer_begin, i8*** %pointer_end, i32* %pointers_size, i8* %arraydecay80, i8** %buffer_begin, i8** %buffer_end, i32* %buffer_size), !dbg !259
  %tobool82 = icmp ne i32 %call81, 0, !dbg !259
  br i1 %tobool82, label %if.end84, label %if.then83, !dbg !260

if.then83:                                        ; preds = %if.then78
  store i32 1, i32* %failed, align 4, !dbg !261
  br label %if.end84, !dbg !263

if.end84:                                         ; preds = %if.then83, %if.then78
  br label %if.end85, !dbg !264

if.end85:                                         ; preds = %if.end84, %for.end
  %35 = load i32, i32* %failed, align 4, !dbg !265
  %tobool86 = icmp ne i32 %35, 0, !dbg !265
  br i1 %tobool86, label %if.end89, label %if.then87, !dbg !267

if.then87:                                        ; preds = %if.end85
  call void @llvm.dbg.declare(metadata i64* %n, metadata !268, metadata !48), !dbg !273
  %36 = load i8**, i8*** %pointer_end, align 8, !dbg !274
  %37 = load i8**, i8*** %pointer_begin, align 8, !dbg !275
  %sub.ptr.lhs.cast = ptrtoint i8** %36 to i64, !dbg !276
  %sub.ptr.rhs.cast = ptrtoint i8** %37 to i64, !dbg !276
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !276
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !276
  store i64 %sub.ptr.div, i64* %n, align 8, !dbg !273
  %38 = load i64, i64* %n, align 8, !dbg !277
  %add = add nsw i64 %38, 1, !dbg !278
  %mul = mul i64 %add, 8, !dbg !279
  %call88 = call noalias i8* @malloc(i64 %mul) #5, !dbg !280
  %39 = bitcast i8* %call88 to i8**, !dbg !281
  store i8** %39, i8*** %newCommand, align 8, !dbg !282
  br label %if.end89, !dbg !283

if.end89:                                         ; preds = %if.then87, %if.end85
  %40 = load i8**, i8*** %newCommand, align 8, !dbg !284
  %tobool90 = icmp ne i8** %40, null, !dbg !284
  br i1 %tobool90, label %if.then91, label %if.else99, !dbg !286

if.then91:                                        ; preds = %if.end89
  call void @llvm.dbg.declare(metadata i64* %n92, metadata !287, metadata !48), !dbg !289
  %41 = load i8**, i8*** %pointer_end, align 8, !dbg !290
  %42 = load i8**, i8*** %pointer_begin, align 8, !dbg !291
  %sub.ptr.lhs.cast93 = ptrtoint i8** %41 to i64, !dbg !292
  %sub.ptr.rhs.cast94 = ptrtoint i8** %42 to i64, !dbg !292
  %sub.ptr.sub95 = sub i64 %sub.ptr.lhs.cast93, %sub.ptr.rhs.cast94, !dbg !292
  %sub.ptr.div96 = sdiv exact i64 %sub.ptr.sub95, 8, !dbg !292
  store i64 %sub.ptr.div96, i64* %n92, align 8, !dbg !289
  %43 = load i8**, i8*** %newCommand, align 8, !dbg !293
  %44 = bitcast i8** %43 to i8*, !dbg !294
  %45 = load i8**, i8*** %pointer_begin, align 8, !dbg !295
  %46 = bitcast i8** %45 to i8*, !dbg !294
  %47 = load i64, i64* %n92, align 8, !dbg !296
  %mul97 = mul i64 8, %47, !dbg !297
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %44, i8* %46, i64 %mul97, i32 8, i1 false), !dbg !294
  %48 = load i64, i64* %n92, align 8, !dbg !298
  %49 = load i8**, i8*** %newCommand, align 8, !dbg !299
  %arrayidx98 = getelementptr inbounds i8*, i8** %49, i64 %48, !dbg !299
  store i8* null, i8** %arrayidx98, align 8, !dbg !300
  br label %if.end103, !dbg !301

if.else99:                                        ; preds = %if.end89
  br label %while.cond, !dbg !302

while.cond:                                       ; preds = %while.body, %if.else99
  %50 = load i8**, i8*** %pointer_end, align 8, !dbg !304
  %51 = load i8**, i8*** %pointer_begin, align 8, !dbg !306
  %cmp100 = icmp ne i8** %50, %51, !dbg !307
  br i1 %cmp100, label %while.body, label %while.end, !dbg !308

while.body:                                       ; preds = %while.cond
  %52 = load i8**, i8*** %pointer_end, align 8, !dbg !309
  %incdec.ptr102 = getelementptr inbounds i8*, i8** %52, i32 -1, !dbg !309
  store i8** %incdec.ptr102, i8*** %pointer_end, align 8, !dbg !309
  %53 = load i8*, i8** %incdec.ptr102, align 8, !dbg !311
  call void @free(i8* %53) #5, !dbg !312
  br label %while.cond, !dbg !313

while.end:                                        ; preds = %while.cond
  br label %if.end103

if.end103:                                        ; preds = %while.end, %if.then91
  %54 = load i8**, i8*** %pointer_begin, align 8, !dbg !315
  %arraydecay104 = getelementptr inbounds [32 x i8*], [32 x i8*]* %local_pointers, i32 0, i32 0, !dbg !317
  %cmp105 = icmp ne i8** %54, %arraydecay104, !dbg !318
  br i1 %cmp105, label %if.then107, label %if.end108, !dbg !319

if.then107:                                       ; preds = %if.end103
  %55 = load i8**, i8*** %pointer_begin, align 8, !dbg !320
  %56 = bitcast i8** %55 to i8*, !dbg !320
  call void @free(i8* %56) #5, !dbg !322
  br label %if.end108, !dbg !323

if.end108:                                        ; preds = %if.then107, %if.end103
  %57 = load i8*, i8** %buffer_begin, align 8, !dbg !324
  %arraydecay109 = getelementptr inbounds [1024 x i8], [1024 x i8]* %local_buffer, i32 0, i32 0, !dbg !326
  %cmp110 = icmp ne i8* %57, %arraydecay109, !dbg !327
  br i1 %cmp110, label %if.then112, label %if.end113, !dbg !328

if.then112:                                       ; preds = %if.end108
  %58 = load i8*, i8** %buffer_begin, align 8, !dbg !329
  call void @free(i8* %58) #5, !dbg !331
  br label %if.end113, !dbg !332

if.end113:                                        ; preds = %if.then112, %if.end108
  %59 = load i32, i32* %flags.addr, align 4, !dbg !333
  %60 = load i8**, i8*** %newCommand, align 8, !dbg !334
  ret i8** %60, !dbg !335
}

; Function Attrs: nounwind uwtable
define internal i32 @kwsysSystem__AppendByte(i8* %local, i8** %begin, i8** %end, i32* %size, i8 signext %c) #0 !dbg !36 {
entry:
  %retval = alloca i32, align 4
  %local.addr = alloca i8*, align 8
  %begin.addr = alloca i8**, align 8
  %end.addr = alloca i8**, align 8
  %size.addr = alloca i32*, align 8
  %c.addr = alloca i8, align 1
  %length = alloca i64, align 8
  %newBuffer = alloca i8*, align 8
  store i8* %local, i8** %local.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %local.addr, metadata !336, metadata !48), !dbg !337
  store i8** %begin, i8*** %begin.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %begin.addr, metadata !338, metadata !48), !dbg !339
  store i8** %end, i8*** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %end.addr, metadata !340, metadata !48), !dbg !341
  store i32* %size, i32** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %size.addr, metadata !342, metadata !48), !dbg !343
  store i8 %c, i8* %c.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %c.addr, metadata !344, metadata !48), !dbg !345
  %0 = load i8**, i8*** %end.addr, align 8, !dbg !346
  %1 = load i8*, i8** %0, align 8, !dbg !348
  %2 = load i8**, i8*** %begin.addr, align 8, !dbg !349
  %3 = load i8*, i8** %2, align 8, !dbg !350
  %sub.ptr.lhs.cast = ptrtoint i8* %1 to i64, !dbg !351
  %sub.ptr.rhs.cast = ptrtoint i8* %3 to i64, !dbg !351
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !351
  %4 = load i32*, i32** %size.addr, align 8, !dbg !352
  %5 = load i32, i32* %4, align 4, !dbg !353
  %conv = sext i32 %5 to i64, !dbg !353
  %cmp = icmp sge i64 %sub.ptr.sub, %conv, !dbg !354
  br i1 %cmp, label %if.then, label %if.end13, !dbg !355

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %length, metadata !356, metadata !48), !dbg !358
  %6 = load i8**, i8*** %end.addr, align 8, !dbg !359
  %7 = load i8*, i8** %6, align 8, !dbg !360
  %8 = load i8**, i8*** %begin.addr, align 8, !dbg !361
  %9 = load i8*, i8** %8, align 8, !dbg !362
  %sub.ptr.lhs.cast2 = ptrtoint i8* %7 to i64, !dbg !363
  %sub.ptr.rhs.cast3 = ptrtoint i8* %9 to i64, !dbg !363
  %sub.ptr.sub4 = sub i64 %sub.ptr.lhs.cast2, %sub.ptr.rhs.cast3, !dbg !363
  store i64 %sub.ptr.sub4, i64* %length, align 8, !dbg !358
  call void @llvm.dbg.declare(metadata i8** %newBuffer, metadata !364, metadata !48), !dbg !365
  %10 = load i32*, i32** %size.addr, align 8, !dbg !366
  %11 = load i32, i32* %10, align 4, !dbg !367
  %mul = mul nsw i32 %11, 2, !dbg !368
  %conv5 = sext i32 %mul to i64, !dbg !369
  %call = call noalias i8* @malloc(i64 %conv5) #5, !dbg !370
  store i8* %call, i8** %newBuffer, align 8, !dbg !365
  %12 = load i8*, i8** %newBuffer, align 8, !dbg !371
  %tobool = icmp ne i8* %12, null, !dbg !371
  br i1 %tobool, label %if.end, label %if.then6, !dbg !373

if.then6:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !374
  br label %return, !dbg !374

if.end:                                           ; preds = %if.then
  %13 = load i8*, i8** %newBuffer, align 8, !dbg !376
  %14 = load i8**, i8*** %begin.addr, align 8, !dbg !377
  %15 = load i8*, i8** %14, align 8, !dbg !378
  %16 = load i64, i64* %length, align 8, !dbg !379
  %mul7 = mul i64 %16, 1, !dbg !380
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* %15, i64 %mul7, i32 1, i1 false), !dbg !381
  %17 = load i8**, i8*** %begin.addr, align 8, !dbg !382
  %18 = load i8*, i8** %17, align 8, !dbg !384
  %19 = load i8*, i8** %local.addr, align 8, !dbg !385
  %cmp8 = icmp ne i8* %18, %19, !dbg !386
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !387

if.then10:                                        ; preds = %if.end
  %20 = load i8**, i8*** %begin.addr, align 8, !dbg !388
  %21 = load i8*, i8** %20, align 8, !dbg !390
  call void @free(i8* %21) #5, !dbg !391
  br label %if.end11, !dbg !392

if.end11:                                         ; preds = %if.then10, %if.end
  %22 = load i8*, i8** %newBuffer, align 8, !dbg !393
  %23 = load i8**, i8*** %begin.addr, align 8, !dbg !394
  store i8* %22, i8** %23, align 8, !dbg !395
  %24 = load i8**, i8*** %begin.addr, align 8, !dbg !396
  %25 = load i8*, i8** %24, align 8, !dbg !397
  %26 = load i64, i64* %length, align 8, !dbg !398
  %add.ptr = getelementptr inbounds i8, i8* %25, i64 %26, !dbg !399
  %27 = load i8**, i8*** %end.addr, align 8, !dbg !400
  store i8* %add.ptr, i8** %27, align 8, !dbg !401
  %28 = load i32*, i32** %size.addr, align 8, !dbg !402
  %29 = load i32, i32* %28, align 4, !dbg !403
  %mul12 = mul nsw i32 %29, 2, !dbg !403
  store i32 %mul12, i32* %28, align 4, !dbg !403
  br label %if.end13, !dbg !404

if.end13:                                         ; preds = %if.end11, %entry
  %30 = load i8, i8* %c.addr, align 1, !dbg !405
  %31 = load i8**, i8*** %end.addr, align 8, !dbg !406
  %32 = load i8*, i8** %31, align 8, !dbg !407
  %incdec.ptr = getelementptr inbounds i8, i8* %32, i32 1, !dbg !407
  store i8* %incdec.ptr, i8** %31, align 8, !dbg !407
  store i8 %30, i8* %32, align 1, !dbg !408
  store i32 1, i32* %retval, align 4, !dbg !409
  br label %return, !dbg !409

return:                                           ; preds = %if.end13, %if.then6
  %33 = load i32, i32* %retval, align 4, !dbg !410
  ret i32 %33, !dbg !410
}

; Function Attrs: nounwind readnone
declare i16** @__ctype_b_loc() #2

; Function Attrs: nounwind uwtable
define internal i32 @kwsysSystem__AppendArgument(i8** %local, i8*** %begin, i8*** %end, i32* %size, i8* %arg_local, i8** %arg_begin, i8** %arg_end, i32* %arg_size) #0 !dbg !40 {
entry:
  %retval = alloca i32, align 4
  %local.addr = alloca i8**, align 8
  %begin.addr = alloca i8***, align 8
  %end.addr = alloca i8***, align 8
  %size.addr = alloca i32*, align 8
  %arg_local.addr = alloca i8*, align 8
  %arg_begin.addr = alloca i8**, align 8
  %arg_end.addr = alloca i8**, align 8
  %arg_size.addr = alloca i32*, align 8
  %length = alloca i64, align 8
  %newPointers = alloca i8**, align 8
  store i8** %local, i8*** %local.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %local.addr, metadata !411, metadata !48), !dbg !412
  store i8*** %begin, i8**** %begin.addr, align 8
  call void @llvm.dbg.declare(metadata i8**** %begin.addr, metadata !413, metadata !48), !dbg !414
  store i8*** %end, i8**** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8**** %end.addr, metadata !415, metadata !48), !dbg !416
  store i32* %size, i32** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %size.addr, metadata !417, metadata !48), !dbg !418
  store i8* %arg_local, i8** %arg_local.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %arg_local.addr, metadata !419, metadata !48), !dbg !420
  store i8** %arg_begin, i8*** %arg_begin.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %arg_begin.addr, metadata !421, metadata !48), !dbg !422
  store i8** %arg_end, i8*** %arg_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %arg_end.addr, metadata !423, metadata !48), !dbg !424
  store i32* %arg_size, i32** %arg_size.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %arg_size.addr, metadata !425, metadata !48), !dbg !426
  %0 = load i8*, i8** %arg_local.addr, align 8, !dbg !427
  %1 = load i8**, i8*** %arg_begin.addr, align 8, !dbg !429
  %2 = load i8**, i8*** %arg_end.addr, align 8, !dbg !430
  %3 = load i32*, i32** %arg_size.addr, align 8, !dbg !431
  %call = call i32 @kwsysSystem__AppendByte(i8* %0, i8** %1, i8** %2, i32* %3, i8 signext 0), !dbg !432
  %tobool = icmp ne i32 %call, 0, !dbg !432
  br i1 %tobool, label %if.end, label %if.then, !dbg !433

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !434
  br label %return, !dbg !434

if.end:                                           ; preds = %entry
  %4 = load i8***, i8**** %end.addr, align 8, !dbg !436
  %5 = load i8**, i8*** %4, align 8, !dbg !438
  %6 = load i8***, i8**** %begin.addr, align 8, !dbg !439
  %7 = load i8**, i8*** %6, align 8, !dbg !440
  %sub.ptr.lhs.cast = ptrtoint i8** %5 to i64, !dbg !441
  %sub.ptr.rhs.cast = ptrtoint i8** %7 to i64, !dbg !441
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !441
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !441
  %8 = load i32*, i32** %size.addr, align 8, !dbg !442
  %9 = load i32, i32* %8, align 4, !dbg !443
  %conv = sext i32 %9 to i64, !dbg !443
  %cmp = icmp sge i64 %sub.ptr.div, %conv, !dbg !444
  br i1 %cmp, label %if.then2, label %if.end19, !dbg !445

if.then2:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %length, metadata !446, metadata !48), !dbg !448
  %10 = load i8***, i8**** %end.addr, align 8, !dbg !449
  %11 = load i8**, i8*** %10, align 8, !dbg !450
  %12 = load i8***, i8**** %begin.addr, align 8, !dbg !451
  %13 = load i8**, i8*** %12, align 8, !dbg !452
  %sub.ptr.lhs.cast3 = ptrtoint i8** %11 to i64, !dbg !453
  %sub.ptr.rhs.cast4 = ptrtoint i8** %13 to i64, !dbg !453
  %sub.ptr.sub5 = sub i64 %sub.ptr.lhs.cast3, %sub.ptr.rhs.cast4, !dbg !453
  %sub.ptr.div6 = sdiv exact i64 %sub.ptr.sub5, 8, !dbg !453
  store i64 %sub.ptr.div6, i64* %length, align 8, !dbg !448
  call void @llvm.dbg.declare(metadata i8*** %newPointers, metadata !454, metadata !48), !dbg !455
  %14 = load i32*, i32** %size.addr, align 8, !dbg !456
  %15 = load i32, i32* %14, align 4, !dbg !457
  %conv7 = sext i32 %15 to i64, !dbg !458
  %mul = mul i64 %conv7, 2, !dbg !459
  %mul8 = mul i64 %mul, 8, !dbg !460
  %call9 = call noalias i8* @malloc(i64 %mul8) #5, !dbg !461
  %16 = bitcast i8* %call9 to i8**, !dbg !462
  store i8** %16, i8*** %newPointers, align 8, !dbg !455
  %17 = load i8**, i8*** %newPointers, align 8, !dbg !463
  %tobool10 = icmp ne i8** %17, null, !dbg !463
  br i1 %tobool10, label %if.end12, label %if.then11, !dbg !465

if.then11:                                        ; preds = %if.then2
  store i32 0, i32* %retval, align 4, !dbg !466
  br label %return, !dbg !466

if.end12:                                         ; preds = %if.then2
  %18 = load i8**, i8*** %newPointers, align 8, !dbg !468
  %19 = bitcast i8** %18 to i8*, !dbg !469
  %20 = load i8***, i8**** %begin.addr, align 8, !dbg !470
  %21 = load i8**, i8*** %20, align 8, !dbg !471
  %22 = bitcast i8** %21 to i8*, !dbg !469
  %23 = load i64, i64* %length, align 8, !dbg !472
  %mul13 = mul i64 %23, 8, !dbg !473
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* %22, i64 %mul13, i32 8, i1 false), !dbg !469
  %24 = load i8***, i8**** %begin.addr, align 8, !dbg !474
  %25 = load i8**, i8*** %24, align 8, !dbg !476
  %26 = load i8**, i8*** %local.addr, align 8, !dbg !477
  %cmp14 = icmp ne i8** %25, %26, !dbg !478
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !479

if.then16:                                        ; preds = %if.end12
  %27 = load i8***, i8**** %begin.addr, align 8, !dbg !480
  %28 = load i8**, i8*** %27, align 8, !dbg !482
  %29 = bitcast i8** %28 to i8*, !dbg !482
  call void @free(i8* %29) #5, !dbg !483
  br label %if.end17, !dbg !484

if.end17:                                         ; preds = %if.then16, %if.end12
  %30 = load i8**, i8*** %newPointers, align 8, !dbg !485
  %31 = load i8***, i8**** %begin.addr, align 8, !dbg !486
  store i8** %30, i8*** %31, align 8, !dbg !487
  %32 = load i8***, i8**** %begin.addr, align 8, !dbg !488
  %33 = load i8**, i8*** %32, align 8, !dbg !489
  %34 = load i64, i64* %length, align 8, !dbg !490
  %add.ptr = getelementptr inbounds i8*, i8** %33, i64 %34, !dbg !491
  %35 = load i8***, i8**** %end.addr, align 8, !dbg !492
  store i8** %add.ptr, i8*** %35, align 8, !dbg !493
  %36 = load i32*, i32** %size.addr, align 8, !dbg !494
  %37 = load i32, i32* %36, align 4, !dbg !495
  %mul18 = mul nsw i32 %37, 2, !dbg !495
  store i32 %mul18, i32* %36, align 4, !dbg !495
  br label %if.end19, !dbg !496

if.end19:                                         ; preds = %if.end17, %if.end
  %38 = load i8**, i8*** %arg_end.addr, align 8, !dbg !497
  %39 = load i8*, i8** %38, align 8, !dbg !498
  %40 = load i8**, i8*** %arg_begin.addr, align 8, !dbg !499
  %41 = load i8*, i8** %40, align 8, !dbg !500
  %sub.ptr.lhs.cast20 = ptrtoint i8* %39 to i64, !dbg !501
  %sub.ptr.rhs.cast21 = ptrtoint i8* %41 to i64, !dbg !501
  %sub.ptr.sub22 = sub i64 %sub.ptr.lhs.cast20, %sub.ptr.rhs.cast21, !dbg !501
  %call23 = call noalias i8* @malloc(i64 %sub.ptr.sub22) #5, !dbg !502
  %42 = load i8***, i8**** %end.addr, align 8, !dbg !503
  %43 = load i8**, i8*** %42, align 8, !dbg !504
  store i8* %call23, i8** %43, align 8, !dbg !505
  %44 = load i8***, i8**** %end.addr, align 8, !dbg !506
  %45 = load i8**, i8*** %44, align 8, !dbg !508
  %46 = load i8*, i8** %45, align 8, !dbg !509
  %tobool24 = icmp ne i8* %46, null, !dbg !509
  br i1 %tobool24, label %if.end26, label %if.then25, !dbg !510

if.then25:                                        ; preds = %if.end19
  store i32 0, i32* %retval, align 4, !dbg !511
  br label %return, !dbg !511

if.end26:                                         ; preds = %if.end19
  %47 = load i8***, i8**** %end.addr, align 8, !dbg !513
  %48 = load i8**, i8*** %47, align 8, !dbg !514
  %49 = load i8*, i8** %48, align 8, !dbg !515
  %50 = load i8**, i8*** %arg_begin.addr, align 8, !dbg !516
  %51 = load i8*, i8** %50, align 8, !dbg !517
  %52 = load i8**, i8*** %arg_end.addr, align 8, !dbg !518
  %53 = load i8*, i8** %52, align 8, !dbg !519
  %54 = load i8**, i8*** %arg_begin.addr, align 8, !dbg !520
  %55 = load i8*, i8** %54, align 8, !dbg !521
  %sub.ptr.lhs.cast27 = ptrtoint i8* %53 to i64, !dbg !522
  %sub.ptr.rhs.cast28 = ptrtoint i8* %55 to i64, !dbg !522
  %sub.ptr.sub29 = sub i64 %sub.ptr.lhs.cast27, %sub.ptr.rhs.cast28, !dbg !522
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %49, i8* %51, i64 %sub.ptr.sub29, i32 1, i1 false), !dbg !523
  %56 = load i8***, i8**** %end.addr, align 8, !dbg !524
  %57 = load i8**, i8*** %56, align 8, !dbg !525
  %incdec.ptr = getelementptr inbounds i8*, i8** %57, i32 1, !dbg !525
  store i8** %incdec.ptr, i8*** %56, align 8, !dbg !525
  %58 = load i8**, i8*** %arg_begin.addr, align 8, !dbg !526
  %59 = load i8*, i8** %58, align 8, !dbg !527
  %60 = load i8**, i8*** %arg_end.addr, align 8, !dbg !528
  store i8* %59, i8** %60, align 8, !dbg !529
  store i32 1, i32* %retval, align 4, !dbg !530
  br label %return, !dbg !530

return:                                           ; preds = %if.end26, %if.then25, %if.then11, %if.then
  %61 = load i32, i32* %retval, align 4, !dbg !531
  ret i32 %61, !dbg !531
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!44, !45}
!llvm.ident = !{!46}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !28)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/System.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 46, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/ctype.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "_ISupper", value: 256)
!7 = !DIEnumerator(name: "_ISlower", value: 512)
!8 = !DIEnumerator(name: "_ISalpha", value: 1024)
!9 = !DIEnumerator(name: "_ISdigit", value: 2048)
!10 = !DIEnumerator(name: "_ISxdigit", value: 4096)
!11 = !DIEnumerator(name: "_ISspace", value: 8192)
!12 = !DIEnumerator(name: "_ISprint", value: 16384)
!13 = !DIEnumerator(name: "_ISgraph", value: 32768)
!14 = !DIEnumerator(name: "_ISblank", value: 1)
!15 = !DIEnumerator(name: "_IScntrl", value: 2)
!16 = !DIEnumerator(name: "_ISpunct", value: 4)
!17 = !DIEnumerator(name: "_ISalnum", value: 8)
!18 = !{!19, !20, !21, !22, !25, !23}
!19 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!20 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!21 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !26, line: 62, baseType: !27)
!26 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!27 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!28 = !{!29, !35, !36, !40}
!29 = distinct !DISubprogram(name: "cmsysSystem_Parse_CommandForUnix", scope: !1, file: !1, line: 227, type: !30, isLocal: false, isDefinition: true, scopeLine: 228, flags: DIFlagPrototyped, isOptimized: false, variables: !34)
!30 = !DISubroutineType(types: !31)
!31 = !{!22, !32, !19}
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !24)
!34 = !{}
!35 = distinct !DISubprogram(name: "kwsysSystem__ParseUnixCommand", scope: !1, file: !1, line: 94, type: !30, isLocal: true, isDefinition: true, scopeLine: 95, flags: DIFlagPrototyped, isOptimized: false, variables: !34)
!36 = distinct !DISubprogram(name: "kwsysSystem__AppendByte", scope: !1, file: !1, line: 25, type: !37, isLocal: true, isDefinition: true, scopeLine: 27, flags: DIFlagPrototyped, isOptimized: false, variables: !34)
!37 = !DISubroutineType(types: !38)
!38 = !{!19, !23, !22, !22, !39, !24}
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!40 = distinct !DISubprogram(name: "kwsysSystem__AppendArgument", scope: !1, file: !1, line: 49, type: !41, isLocal: true, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !34)
!41 = !DISubroutineType(types: !42)
!42 = !{!19, !22, !43, !43, !39, !23, !22, !22, !39}
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!44 = !{i32 2, !"Dwarf Version", i32 4}
!45 = !{i32 2, !"Debug Info Version", i32 3}
!46 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!47 = !DILocalVariable(name: "command", arg: 1, scope: !29, file: !1, line: 227, type: !32)
!48 = !DIExpression()
!49 = !DILocation(line: 227, column: 53, scope: !29)
!50 = !DILocalVariable(name: "flags", arg: 2, scope: !29, file: !1, line: 227, type: !19)
!51 = !DILocation(line: 227, column: 66, scope: !29)
!52 = !DILocation(line: 230, column: 7, scope: !53)
!53 = distinct !DILexicalBlock(scope: !29, file: !1, line: 230, column: 7)
!54 = !DILocation(line: 230, column: 13, scope: !53)
!55 = !DILocation(line: 230, column: 7, scope: !29)
!56 = !DILocation(line: 231, column: 5, scope: !57)
!57 = distinct !DILexicalBlock(scope: !53, file: !1, line: 230, column: 19)
!58 = !DILocation(line: 235, column: 40, scope: !29)
!59 = !DILocation(line: 235, column: 49, scope: !29)
!60 = !DILocation(line: 235, column: 10, scope: !29)
!61 = !DILocation(line: 235, column: 3, scope: !29)
!62 = !DILocation(line: 236, column: 1, scope: !29)
!63 = !DILocalVariable(name: "command", arg: 1, scope: !35, file: !1, line: 94, type: !32)
!64 = !DILocation(line: 94, column: 57, scope: !35)
!65 = !DILocalVariable(name: "flags", arg: 2, scope: !35, file: !1, line: 94, type: !19)
!66 = !DILocation(line: 94, column: 70, scope: !35)
!67 = !DILocalVariable(name: "local_pointers", scope: !35, file: !1, line: 97, type: !68)
!68 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 2048, align: 64, elements: !69)
!69 = !{!70}
!70 = !DISubrange(count: 32)
!71 = !DILocation(line: 97, column: 9, scope: !35)
!72 = !DILocalVariable(name: "pointers_size", scope: !35, file: !1, line: 98, type: !19)
!73 = !DILocation(line: 98, column: 7, scope: !35)
!74 = !DILocalVariable(name: "pointer_begin", scope: !35, file: !1, line: 99, type: !22)
!75 = !DILocation(line: 99, column: 10, scope: !35)
!76 = !DILocation(line: 99, column: 26, scope: !35)
!77 = !DILocalVariable(name: "pointer_end", scope: !35, file: !1, line: 100, type: !22)
!78 = !DILocation(line: 100, column: 10, scope: !35)
!79 = !DILocation(line: 100, column: 24, scope: !35)
!80 = !DILocalVariable(name: "local_buffer", scope: !35, file: !1, line: 103, type: !81)
!81 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 8192, align: 8, elements: !82)
!82 = !{!83}
!83 = !DISubrange(count: 1024)
!84 = !DILocation(line: 103, column: 8, scope: !35)
!85 = !DILocalVariable(name: "buffer_size", scope: !35, file: !1, line: 104, type: !19)
!86 = !DILocation(line: 104, column: 7, scope: !35)
!87 = !DILocalVariable(name: "buffer_begin", scope: !35, file: !1, line: 105, type: !23)
!88 = !DILocation(line: 105, column: 9, scope: !35)
!89 = !DILocation(line: 105, column: 24, scope: !35)
!90 = !DILocalVariable(name: "buffer_end", scope: !35, file: !1, line: 106, type: !23)
!91 = !DILocation(line: 106, column: 9, scope: !35)
!92 = !DILocation(line: 106, column: 22, scope: !35)
!93 = !DILocalVariable(name: "newCommand", scope: !35, file: !1, line: 109, type: !22)
!94 = !DILocation(line: 109, column: 10, scope: !35)
!95 = !DILocalVariable(name: "c", scope: !35, file: !1, line: 110, type: !32)
!96 = !DILocation(line: 110, column: 15, scope: !35)
!97 = !DILocation(line: 110, column: 19, scope: !35)
!98 = !DILocalVariable(name: "in_argument", scope: !35, file: !1, line: 111, type: !19)
!99 = !DILocation(line: 111, column: 7, scope: !35)
!100 = !DILocalVariable(name: "in_escape", scope: !35, file: !1, line: 112, type: !19)
!101 = !DILocation(line: 112, column: 7, scope: !35)
!102 = !DILocalVariable(name: "in_single", scope: !35, file: !1, line: 113, type: !19)
!103 = !DILocation(line: 113, column: 7, scope: !35)
!104 = !DILocalVariable(name: "in_double", scope: !35, file: !1, line: 114, type: !19)
!105 = !DILocation(line: 114, column: 7, scope: !35)
!106 = !DILocalVariable(name: "failed", scope: !35, file: !1, line: 115, type: !19)
!107 = !DILocation(line: 115, column: 7, scope: !35)
!108 = !DILocation(line: 116, column: 3, scope: !35)
!109 = !DILocation(line: 116, column: 11, scope: !110)
!110 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 1)
!111 = distinct !DILexicalBlock(scope: !112, file: !1, line: 116, column: 3)
!112 = distinct !DILexicalBlock(scope: !35, file: !1, line: 116, column: 3)
!113 = !DILocation(line: 116, column: 10, scope: !110)
!114 = !DILocation(line: 116, column: 3, scope: !110)
!115 = !DILocation(line: 117, column: 9, scope: !116)
!116 = distinct !DILexicalBlock(scope: !117, file: !1, line: 117, column: 9)
!117 = distinct !DILexicalBlock(scope: !111, file: !1, line: 116, column: 19)
!118 = !DILocation(line: 117, column: 9, scope: !117)
!119 = !DILocation(line: 119, column: 12, scope: !120)
!120 = distinct !DILexicalBlock(scope: !121, file: !1, line: 119, column: 11)
!121 = distinct !DILexicalBlock(scope: !116, file: !1, line: 117, column: 20)
!122 = !DILocation(line: 119, column: 11, scope: !121)
!123 = !DILocation(line: 120, column: 21, scope: !124)
!124 = distinct !DILexicalBlock(scope: !120, file: !1, line: 119, column: 25)
!125 = !DILocation(line: 121, column: 7, scope: !124)
!126 = !DILocation(line: 122, column: 36, scope: !127)
!127 = distinct !DILexicalBlock(scope: !121, file: !1, line: 122, column: 11)
!128 = !DILocation(line: 123, column: 51, scope: !127)
!129 = !DILocation(line: 123, column: 50, scope: !127)
!130 = !DILocation(line: 122, column: 12, scope: !127)
!131 = !DILocation(line: 122, column: 11, scope: !121)
!132 = !DILocation(line: 124, column: 16, scope: !133)
!133 = distinct !DILexicalBlock(scope: !127, file: !1, line: 123, column: 55)
!134 = !DILocation(line: 125, column: 9, scope: !133)
!135 = !DILocation(line: 127, column: 17, scope: !121)
!136 = !DILocation(line: 128, column: 5, scope: !121)
!137 = !DILocation(line: 128, column: 17, scope: !138)
!138 = !DILexicalBlockFile(scope: !139, file: !1, discriminator: 1)
!139 = distinct !DILexicalBlock(scope: !116, file: !1, line: 128, column: 16)
!140 = !DILocation(line: 128, column: 16, scope: !138)
!141 = !DILocation(line: 128, column: 19, scope: !138)
!142 = !DILocation(line: 130, column: 17, scope: !143)
!143 = distinct !DILexicalBlock(scope: !139, file: !1, line: 128, column: 28)
!144 = !DILocation(line: 131, column: 5, scope: !143)
!145 = !DILocation(line: 131, column: 17, scope: !146)
!146 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 1)
!147 = distinct !DILexicalBlock(scope: !139, file: !1, line: 131, column: 16)
!148 = !DILocation(line: 131, column: 16, scope: !146)
!149 = !DILocation(line: 131, column: 19, scope: !146)
!150 = !DILocation(line: 131, column: 27, scope: !146)
!151 = !DILocation(line: 131, column: 31, scope: !152)
!152 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 2)
!153 = !DILocation(line: 131, column: 16, scope: !152)
!154 = !DILocation(line: 133, column: 11, scope: !155)
!155 = distinct !DILexicalBlock(scope: !156, file: !1, line: 133, column: 11)
!156 = distinct !DILexicalBlock(scope: !147, file: !1, line: 131, column: 42)
!157 = !DILocation(line: 133, column: 11, scope: !156)
!158 = !DILocation(line: 134, column: 19, scope: !159)
!159 = distinct !DILexicalBlock(scope: !155, file: !1, line: 133, column: 22)
!160 = !DILocation(line: 135, column: 7, scope: !159)
!161 = !DILocation(line: 136, column: 19, scope: !162)
!162 = distinct !DILexicalBlock(scope: !155, file: !1, line: 135, column: 14)
!163 = !DILocation(line: 137, column: 14, scope: !164)
!164 = distinct !DILexicalBlock(scope: !162, file: !1, line: 137, column: 13)
!165 = !DILocation(line: 137, column: 13, scope: !162)
!166 = !DILocation(line: 138, column: 23, scope: !167)
!167 = distinct !DILexicalBlock(scope: !164, file: !1, line: 137, column: 27)
!168 = !DILocation(line: 139, column: 9, scope: !167)
!169 = !DILocation(line: 141, column: 5, scope: !156)
!170 = !DILocation(line: 141, column: 17, scope: !171)
!171 = !DILexicalBlockFile(scope: !172, file: !1, discriminator: 1)
!172 = distinct !DILexicalBlock(scope: !147, file: !1, line: 141, column: 16)
!173 = !DILocation(line: 141, column: 16, scope: !171)
!174 = !DILocation(line: 141, column: 19, scope: !171)
!175 = !DILocation(line: 141, column: 26, scope: !171)
!176 = !DILocation(line: 141, column: 30, scope: !177)
!177 = !DILexicalBlockFile(scope: !172, file: !1, discriminator: 2)
!178 = !DILocation(line: 141, column: 16, scope: !177)
!179 = !DILocation(line: 143, column: 11, scope: !180)
!180 = distinct !DILexicalBlock(scope: !181, file: !1, line: 143, column: 11)
!181 = distinct !DILexicalBlock(scope: !172, file: !1, line: 141, column: 41)
!182 = !DILocation(line: 143, column: 11, scope: !181)
!183 = !DILocation(line: 144, column: 19, scope: !184)
!184 = distinct !DILexicalBlock(scope: !180, file: !1, line: 143, column: 22)
!185 = !DILocation(line: 145, column: 7, scope: !184)
!186 = !DILocation(line: 146, column: 19, scope: !187)
!187 = distinct !DILexicalBlock(scope: !180, file: !1, line: 145, column: 14)
!188 = !DILocation(line: 147, column: 14, scope: !189)
!189 = distinct !DILexicalBlock(scope: !187, file: !1, line: 147, column: 13)
!190 = !DILocation(line: 147, column: 13, scope: !187)
!191 = !DILocation(line: 148, column: 23, scope: !192)
!192 = distinct !DILexicalBlock(scope: !189, file: !1, line: 147, column: 27)
!193 = !DILocation(line: 149, column: 9, scope: !192)
!194 = !DILocation(line: 151, column: 5, scope: !181)
!195 = !DILocation(line: 151, column: 16, scope: !196)
!196 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!197 = distinct !DILexicalBlock(scope: !172, file: !1, line: 151, column: 16)
!198 = !DILocation(line: 152, column: 11, scope: !199)
!199 = distinct !DILexicalBlock(scope: !200, file: !1, line: 152, column: 11)
!200 = distinct !DILexicalBlock(scope: !197, file: !1, line: 151, column: 44)
!201 = !DILocation(line: 152, column: 11, scope: !200)
!202 = !DILocation(line: 153, column: 13, scope: !203)
!203 = distinct !DILexicalBlock(scope: !204, file: !1, line: 153, column: 13)
!204 = distinct !DILexicalBlock(scope: !199, file: !1, line: 152, column: 24)
!205 = !DILocation(line: 153, column: 23, scope: !203)
!206 = !DILocation(line: 153, column: 26, scope: !207)
!207 = !DILexicalBlockFile(scope: !203, file: !1, discriminator: 1)
!208 = !DILocation(line: 153, column: 13, scope: !207)
!209 = !DILocation(line: 155, column: 40, scope: !210)
!210 = distinct !DILexicalBlock(scope: !211, file: !1, line: 155, column: 15)
!211 = distinct !DILexicalBlock(scope: !203, file: !1, line: 153, column: 37)
!212 = !DILocation(line: 156, column: 68, scope: !210)
!213 = !DILocation(line: 156, column: 67, scope: !210)
!214 = !DILocation(line: 155, column: 16, scope: !210)
!215 = !DILocation(line: 155, column: 15, scope: !211)
!216 = !DILocation(line: 157, column: 20, scope: !217)
!217 = distinct !DILexicalBlock(scope: !210, file: !1, line: 156, column: 72)
!218 = !DILocation(line: 158, column: 13, scope: !217)
!219 = !DILocation(line: 160, column: 9, scope: !211)
!220 = !DILocation(line: 163, column: 17, scope: !221)
!221 = distinct !DILexicalBlock(scope: !222, file: !1, line: 162, column: 15)
!222 = distinct !DILexicalBlock(scope: !203, file: !1, line: 160, column: 16)
!223 = !DILocation(line: 164, column: 17, scope: !221)
!224 = !DILocation(line: 162, column: 16, scope: !221)
!225 = !DILocation(line: 162, column: 15, scope: !222)
!226 = !DILocation(line: 165, column: 20, scope: !227)
!227 = distinct !DILexicalBlock(scope: !221, file: !1, line: 164, column: 74)
!228 = !DILocation(line: 166, column: 13, scope: !227)
!229 = !DILocation(line: 168, column: 23, scope: !222)
!230 = !DILocation(line: 170, column: 7, scope: !204)
!231 = !DILocation(line: 171, column: 5, scope: !200)
!232 = !DILocation(line: 173, column: 12, scope: !233)
!233 = distinct !DILexicalBlock(scope: !234, file: !1, line: 173, column: 11)
!234 = distinct !DILexicalBlock(scope: !197, file: !1, line: 171, column: 12)
!235 = !DILocation(line: 173, column: 11, scope: !234)
!236 = !DILocation(line: 174, column: 21, scope: !237)
!237 = distinct !DILexicalBlock(scope: !233, file: !1, line: 173, column: 25)
!238 = !DILocation(line: 175, column: 7, scope: !237)
!239 = !DILocation(line: 176, column: 36, scope: !240)
!240 = distinct !DILexicalBlock(scope: !234, file: !1, line: 176, column: 11)
!241 = !DILocation(line: 177, column: 51, scope: !240)
!242 = !DILocation(line: 177, column: 50, scope: !240)
!243 = !DILocation(line: 176, column: 12, scope: !240)
!244 = !DILocation(line: 176, column: 11, scope: !234)
!245 = !DILocation(line: 178, column: 16, scope: !246)
!246 = distinct !DILexicalBlock(scope: !240, file: !1, line: 177, column: 55)
!247 = !DILocation(line: 179, column: 9, scope: !246)
!248 = !DILocation(line: 182, column: 3, scope: !117)
!249 = !DILocation(line: 116, column: 14, scope: !250)
!250 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 2)
!251 = !DILocation(line: 116, column: 3, scope: !250)
!252 = !DILocation(line: 185, column: 7, scope: !253)
!253 = distinct !DILexicalBlock(scope: !35, file: !1, line: 185, column: 7)
!254 = !DILocation(line: 185, column: 7, scope: !35)
!255 = !DILocation(line: 187, column: 11, scope: !256)
!256 = distinct !DILexicalBlock(scope: !257, file: !1, line: 186, column: 9)
!257 = distinct !DILexicalBlock(scope: !253, file: !1, line: 185, column: 20)
!258 = !DILocation(line: 188, column: 11, scope: !256)
!259 = !DILocation(line: 186, column: 10, scope: !256)
!260 = !DILocation(line: 186, column: 9, scope: !257)
!261 = !DILocation(line: 189, column: 14, scope: !262)
!262 = distinct !DILexicalBlock(scope: !256, file: !1, line: 188, column: 68)
!263 = !DILocation(line: 190, column: 5, scope: !262)
!264 = !DILocation(line: 191, column: 3, scope: !257)
!265 = !DILocation(line: 195, column: 8, scope: !266)
!266 = distinct !DILexicalBlock(scope: !35, file: !1, line: 195, column: 7)
!267 = !DILocation(line: 195, column: 7, scope: !35)
!268 = !DILocalVariable(name: "n", scope: !269, file: !1, line: 196, type: !270)
!269 = distinct !DILexicalBlock(scope: !266, file: !1, line: 195, column: 16)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "kwsysSystem_ptrdiff_t", file: !1, line: 20, baseType: !271)
!271 = !DIDerivedType(tag: DW_TAG_typedef, name: "ptrdiff_t", file: !26, line: 51, baseType: !272)
!272 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!273 = !DILocation(line: 196, column: 27, scope: !269)
!274 = !DILocation(line: 196, column: 31, scope: !269)
!275 = !DILocation(line: 196, column: 45, scope: !269)
!276 = !DILocation(line: 196, column: 43, scope: !269)
!277 = !DILocation(line: 197, column: 42, scope: !269)
!278 = !DILocation(line: 197, column: 44, scope: !269)
!279 = !DILocation(line: 197, column: 49, scope: !269)
!280 = !DILocation(line: 197, column: 26, scope: !269)
!281 = !DILocation(line: 197, column: 18, scope: !269)
!282 = !DILocation(line: 197, column: 16, scope: !269)
!283 = !DILocation(line: 198, column: 3, scope: !269)
!284 = !DILocation(line: 200, column: 7, scope: !285)
!285 = distinct !DILexicalBlock(scope: !35, file: !1, line: 200, column: 7)
!286 = !DILocation(line: 200, column: 7, scope: !35)
!287 = !DILocalVariable(name: "n", scope: !288, file: !1, line: 202, type: !270)
!288 = distinct !DILexicalBlock(scope: !285, file: !1, line: 200, column: 19)
!289 = !DILocation(line: 202, column: 27, scope: !288)
!290 = !DILocation(line: 202, column: 31, scope: !288)
!291 = !DILocation(line: 202, column: 45, scope: !288)
!292 = !DILocation(line: 202, column: 43, scope: !288)
!293 = !DILocation(line: 203, column: 12, scope: !288)
!294 = !DILocation(line: 203, column: 5, scope: !288)
!295 = !DILocation(line: 203, column: 24, scope: !288)
!296 = !DILocation(line: 203, column: 64, scope: !288)
!297 = !DILocation(line: 203, column: 53, scope: !288)
!298 = !DILocation(line: 204, column: 16, scope: !288)
!299 = !DILocation(line: 204, column: 5, scope: !288)
!300 = !DILocation(line: 204, column: 19, scope: !288)
!301 = !DILocation(line: 205, column: 3, scope: !288)
!302 = !DILocation(line: 207, column: 5, scope: !303)
!303 = distinct !DILexicalBlock(scope: !285, file: !1, line: 205, column: 10)
!304 = !DILocation(line: 207, column: 12, scope: !305)
!305 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 1)
!306 = !DILocation(line: 207, column: 27, scope: !305)
!307 = !DILocation(line: 207, column: 24, scope: !305)
!308 = !DILocation(line: 207, column: 5, scope: !305)
!309 = !DILocation(line: 208, column: 14, scope: !310)
!310 = distinct !DILexicalBlock(scope: !303, file: !1, line: 207, column: 42)
!311 = !DILocation(line: 208, column: 12, scope: !310)
!312 = !DILocation(line: 208, column: 7, scope: !310)
!313 = !DILocation(line: 207, column: 5, scope: !314)
!314 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 2)
!315 = !DILocation(line: 213, column: 7, scope: !316)
!316 = distinct !DILexicalBlock(scope: !35, file: !1, line: 213, column: 7)
!317 = !DILocation(line: 213, column: 24, scope: !316)
!318 = !DILocation(line: 213, column: 21, scope: !316)
!319 = !DILocation(line: 213, column: 7, scope: !35)
!320 = !DILocation(line: 214, column: 10, scope: !321)
!321 = distinct !DILexicalBlock(scope: !316, file: !1, line: 213, column: 40)
!322 = !DILocation(line: 214, column: 5, scope: !321)
!323 = !DILocation(line: 215, column: 3, scope: !321)
!324 = !DILocation(line: 216, column: 7, scope: !325)
!325 = distinct !DILexicalBlock(scope: !35, file: !1, line: 216, column: 7)
!326 = !DILocation(line: 216, column: 23, scope: !325)
!327 = !DILocation(line: 216, column: 20, scope: !325)
!328 = !DILocation(line: 216, column: 7, scope: !35)
!329 = !DILocation(line: 217, column: 10, scope: !330)
!330 = distinct !DILexicalBlock(scope: !325, file: !1, line: 216, column: 37)
!331 = !DILocation(line: 217, column: 5, scope: !330)
!332 = !DILocation(line: 218, column: 3, scope: !330)
!333 = !DILocation(line: 221, column: 9, scope: !35)
!334 = !DILocation(line: 224, column: 10, scope: !35)
!335 = !DILocation(line: 224, column: 3, scope: !35)
!336 = !DILocalVariable(name: "local", arg: 1, scope: !36, file: !1, line: 25, type: !23)
!337 = !DILocation(line: 25, column: 42, scope: !36)
!338 = !DILocalVariable(name: "begin", arg: 2, scope: !36, file: !1, line: 25, type: !22)
!339 = !DILocation(line: 25, column: 56, scope: !36)
!340 = !DILocalVariable(name: "end", arg: 3, scope: !36, file: !1, line: 25, type: !22)
!341 = !DILocation(line: 25, column: 70, scope: !36)
!342 = !DILocalVariable(name: "size", arg: 4, scope: !36, file: !1, line: 26, type: !39)
!343 = !DILocation(line: 26, column: 41, scope: !36)
!344 = !DILocalVariable(name: "c", arg: 5, scope: !36, file: !1, line: 26, type: !24)
!345 = !DILocation(line: 26, column: 52, scope: !36)
!346 = !DILocation(line: 29, column: 9, scope: !347)
!347 = distinct !DILexicalBlock(scope: !36, file: !1, line: 29, column: 7)
!348 = !DILocation(line: 29, column: 8, scope: !347)
!349 = !DILocation(line: 29, column: 16, scope: !347)
!350 = !DILocation(line: 29, column: 15, scope: !347)
!351 = !DILocation(line: 29, column: 13, scope: !347)
!352 = !DILocation(line: 29, column: 27, scope: !347)
!353 = !DILocation(line: 29, column: 26, scope: !347)
!354 = !DILocation(line: 29, column: 23, scope: !347)
!355 = !DILocation(line: 29, column: 7, scope: !36)
!356 = !DILocalVariable(name: "length", scope: !357, file: !1, line: 30, type: !270)
!357 = distinct !DILexicalBlock(scope: !347, file: !1, line: 29, column: 33)
!358 = !DILocation(line: 30, column: 27, scope: !357)
!359 = !DILocation(line: 30, column: 37, scope: !357)
!360 = !DILocation(line: 30, column: 36, scope: !357)
!361 = !DILocation(line: 30, column: 44, scope: !357)
!362 = !DILocation(line: 30, column: 43, scope: !357)
!363 = !DILocation(line: 30, column: 41, scope: !357)
!364 = !DILocalVariable(name: "newBuffer", scope: !357, file: !1, line: 31, type: !23)
!365 = !DILocation(line: 31, column: 11, scope: !357)
!366 = !DILocation(line: 31, column: 47, scope: !357)
!367 = !DILocation(line: 31, column: 46, scope: !357)
!368 = !DILocation(line: 31, column: 52, scope: !357)
!369 = !DILocation(line: 31, column: 37, scope: !357)
!370 = !DILocation(line: 31, column: 30, scope: !357)
!371 = !DILocation(line: 32, column: 10, scope: !372)
!372 = distinct !DILexicalBlock(scope: !357, file: !1, line: 32, column: 9)
!373 = !DILocation(line: 32, column: 9, scope: !357)
!374 = !DILocation(line: 33, column: 7, scope: !375)
!375 = distinct !DILexicalBlock(scope: !372, file: !1, line: 32, column: 21)
!376 = !DILocation(line: 35, column: 12, scope: !357)
!377 = !DILocation(line: 35, column: 24, scope: !357)
!378 = !DILocation(line: 35, column: 23, scope: !357)
!379 = !DILocation(line: 35, column: 40, scope: !357)
!380 = !DILocation(line: 35, column: 48, scope: !357)
!381 = !DILocation(line: 35, column: 5, scope: !357)
!382 = !DILocation(line: 36, column: 10, scope: !383)
!383 = distinct !DILexicalBlock(scope: !357, file: !1, line: 36, column: 9)
!384 = !DILocation(line: 36, column: 9, scope: !383)
!385 = !DILocation(line: 36, column: 19, scope: !383)
!386 = !DILocation(line: 36, column: 16, scope: !383)
!387 = !DILocation(line: 36, column: 9, scope: !357)
!388 = !DILocation(line: 37, column: 13, scope: !389)
!389 = distinct !DILexicalBlock(scope: !383, file: !1, line: 36, column: 26)
!390 = !DILocation(line: 37, column: 12, scope: !389)
!391 = !DILocation(line: 37, column: 7, scope: !389)
!392 = !DILocation(line: 38, column: 5, scope: !389)
!393 = !DILocation(line: 39, column: 14, scope: !357)
!394 = !DILocation(line: 39, column: 6, scope: !357)
!395 = !DILocation(line: 39, column: 12, scope: !357)
!396 = !DILocation(line: 40, column: 13, scope: !357)
!397 = !DILocation(line: 40, column: 12, scope: !357)
!398 = !DILocation(line: 40, column: 21, scope: !357)
!399 = !DILocation(line: 40, column: 19, scope: !357)
!400 = !DILocation(line: 40, column: 6, scope: !357)
!401 = !DILocation(line: 40, column: 10, scope: !357)
!402 = !DILocation(line: 41, column: 6, scope: !357)
!403 = !DILocation(line: 41, column: 11, scope: !357)
!404 = !DILocation(line: 42, column: 3, scope: !357)
!405 = !DILocation(line: 45, column: 15, scope: !36)
!406 = !DILocation(line: 45, column: 6, scope: !36)
!407 = !DILocation(line: 45, column: 10, scope: !36)
!408 = !DILocation(line: 45, column: 13, scope: !36)
!409 = !DILocation(line: 46, column: 3, scope: !36)
!410 = !DILocation(line: 47, column: 1, scope: !36)
!411 = !DILocalVariable(name: "local", arg: 1, scope: !40, file: !1, line: 49, type: !22)
!412 = !DILocation(line: 49, column: 47, scope: !40)
!413 = !DILocalVariable(name: "begin", arg: 2, scope: !40, file: !1, line: 49, type: !43)
!414 = !DILocation(line: 49, column: 62, scope: !40)
!415 = !DILocalVariable(name: "end", arg: 3, scope: !40, file: !1, line: 50, type: !43)
!416 = !DILocation(line: 50, column: 48, scope: !40)
!417 = !DILocalVariable(name: "size", arg: 4, scope: !40, file: !1, line: 50, type: !39)
!418 = !DILocation(line: 50, column: 58, scope: !40)
!419 = !DILocalVariable(name: "arg_local", arg: 5, scope: !40, file: !1, line: 50, type: !23)
!420 = !DILocation(line: 50, column: 70, scope: !40)
!421 = !DILocalVariable(name: "arg_begin", arg: 6, scope: !40, file: !1, line: 51, type: !22)
!422 = !DILocation(line: 51, column: 47, scope: !40)
!423 = !DILocalVariable(name: "arg_end", arg: 7, scope: !40, file: !1, line: 51, type: !22)
!424 = !DILocation(line: 51, column: 65, scope: !40)
!425 = !DILocalVariable(name: "arg_size", arg: 8, scope: !40, file: !1, line: 52, type: !39)
!426 = !DILocation(line: 52, column: 45, scope: !40)
!427 = !DILocation(line: 55, column: 32, scope: !428)
!428 = distinct !DILexicalBlock(scope: !40, file: !1, line: 55, column: 7)
!429 = !DILocation(line: 55, column: 43, scope: !428)
!430 = !DILocation(line: 55, column: 54, scope: !428)
!431 = !DILocation(line: 55, column: 63, scope: !428)
!432 = !DILocation(line: 55, column: 8, scope: !428)
!433 = !DILocation(line: 55, column: 7, scope: !40)
!434 = !DILocation(line: 57, column: 5, scope: !435)
!435 = distinct !DILexicalBlock(scope: !428, file: !1, line: 56, column: 39)
!436 = !DILocation(line: 61, column: 9, scope: !437)
!437 = distinct !DILexicalBlock(scope: !40, file: !1, line: 61, column: 7)
!438 = !DILocation(line: 61, column: 8, scope: !437)
!439 = !DILocation(line: 61, column: 16, scope: !437)
!440 = !DILocation(line: 61, column: 15, scope: !437)
!441 = !DILocation(line: 61, column: 13, scope: !437)
!442 = !DILocation(line: 61, column: 27, scope: !437)
!443 = !DILocation(line: 61, column: 26, scope: !437)
!444 = !DILocation(line: 61, column: 23, scope: !437)
!445 = !DILocation(line: 61, column: 7, scope: !40)
!446 = !DILocalVariable(name: "length", scope: !447, file: !1, line: 62, type: !270)
!447 = distinct !DILexicalBlock(scope: !437, file: !1, line: 61, column: 33)
!448 = !DILocation(line: 62, column: 27, scope: !447)
!449 = !DILocation(line: 62, column: 37, scope: !447)
!450 = !DILocation(line: 62, column: 36, scope: !447)
!451 = !DILocation(line: 62, column: 44, scope: !447)
!452 = !DILocation(line: 62, column: 43, scope: !447)
!453 = !DILocation(line: 62, column: 41, scope: !447)
!454 = !DILocalVariable(name: "newPointers", scope: !447, file: !1, line: 63, type: !22)
!455 = !DILocation(line: 63, column: 12, scope: !447)
!456 = !DILocation(line: 63, column: 51, scope: !447)
!457 = !DILocation(line: 63, column: 50, scope: !447)
!458 = !DILocation(line: 63, column: 41, scope: !447)
!459 = !DILocation(line: 63, column: 57, scope: !447)
!460 = !DILocation(line: 63, column: 61, scope: !447)
!461 = !DILocation(line: 63, column: 34, scope: !447)
!462 = !DILocation(line: 63, column: 26, scope: !447)
!463 = !DILocation(line: 64, column: 10, scope: !464)
!464 = distinct !DILexicalBlock(scope: !447, file: !1, line: 64, column: 9)
!465 = !DILocation(line: 64, column: 9, scope: !447)
!466 = !DILocation(line: 65, column: 7, scope: !467)
!467 = distinct !DILexicalBlock(scope: !464, file: !1, line: 64, column: 23)
!468 = !DILocation(line: 67, column: 12, scope: !447)
!469 = !DILocation(line: 67, column: 5, scope: !447)
!470 = !DILocation(line: 67, column: 26, scope: !447)
!471 = !DILocation(line: 67, column: 25, scope: !447)
!472 = !DILocation(line: 67, column: 42, scope: !447)
!473 = !DILocation(line: 67, column: 50, scope: !447)
!474 = !DILocation(line: 68, column: 10, scope: !475)
!475 = distinct !DILexicalBlock(scope: !447, file: !1, line: 68, column: 9)
!476 = !DILocation(line: 68, column: 9, scope: !475)
!477 = !DILocation(line: 68, column: 19, scope: !475)
!478 = !DILocation(line: 68, column: 16, scope: !475)
!479 = !DILocation(line: 68, column: 9, scope: !447)
!480 = !DILocation(line: 69, column: 13, scope: !481)
!481 = distinct !DILexicalBlock(scope: !475, file: !1, line: 68, column: 26)
!482 = !DILocation(line: 69, column: 12, scope: !481)
!483 = !DILocation(line: 69, column: 7, scope: !481)
!484 = !DILocation(line: 70, column: 5, scope: !481)
!485 = !DILocation(line: 71, column: 14, scope: !447)
!486 = !DILocation(line: 71, column: 6, scope: !447)
!487 = !DILocation(line: 71, column: 12, scope: !447)
!488 = !DILocation(line: 72, column: 13, scope: !447)
!489 = !DILocation(line: 72, column: 12, scope: !447)
!490 = !DILocation(line: 72, column: 21, scope: !447)
!491 = !DILocation(line: 72, column: 19, scope: !447)
!492 = !DILocation(line: 72, column: 6, scope: !447)
!493 = !DILocation(line: 72, column: 10, scope: !447)
!494 = !DILocation(line: 73, column: 6, scope: !447)
!495 = !DILocation(line: 73, column: 11, scope: !447)
!496 = !DILocation(line: 74, column: 3, scope: !447)
!497 = !DILocation(line: 77, column: 35, scope: !40)
!498 = !DILocation(line: 77, column: 34, scope: !40)
!499 = !DILocation(line: 77, column: 46, scope: !40)
!500 = !DILocation(line: 77, column: 45, scope: !40)
!501 = !DILocation(line: 77, column: 43, scope: !40)
!502 = !DILocation(line: 77, column: 18, scope: !40)
!503 = !DILocation(line: 77, column: 5, scope: !40)
!504 = !DILocation(line: 77, column: 4, scope: !40)
!505 = !DILocation(line: 77, column: 9, scope: !40)
!506 = !DILocation(line: 78, column: 10, scope: !507)
!507 = distinct !DILexicalBlock(scope: !40, file: !1, line: 78, column: 7)
!508 = !DILocation(line: 78, column: 9, scope: !507)
!509 = !DILocation(line: 78, column: 8, scope: !507)
!510 = !DILocation(line: 78, column: 7, scope: !40)
!511 = !DILocation(line: 79, column: 5, scope: !512)
!512 = distinct !DILexicalBlock(scope: !507, file: !1, line: 78, column: 15)
!513 = !DILocation(line: 83, column: 12, scope: !40)
!514 = !DILocation(line: 83, column: 11, scope: !40)
!515 = !DILocation(line: 83, column: 10, scope: !40)
!516 = !DILocation(line: 83, column: 18, scope: !40)
!517 = !DILocation(line: 83, column: 17, scope: !40)
!518 = !DILocation(line: 83, column: 39, scope: !40)
!519 = !DILocation(line: 83, column: 38, scope: !40)
!520 = !DILocation(line: 83, column: 50, scope: !40)
!521 = !DILocation(line: 83, column: 49, scope: !40)
!522 = !DILocation(line: 83, column: 47, scope: !40)
!523 = !DILocation(line: 83, column: 3, scope: !40)
!524 = !DILocation(line: 84, column: 7, scope: !40)
!525 = !DILocation(line: 84, column: 3, scope: !40)
!526 = !DILocation(line: 87, column: 15, scope: !40)
!527 = !DILocation(line: 87, column: 14, scope: !40)
!528 = !DILocation(line: 87, column: 4, scope: !40)
!529 = !DILocation(line: 87, column: 12, scope: !40)
!530 = !DILocation(line: 89, column: 3, scope: !40)
!531 = !DILocation(line: 90, column: 1, scope: !40)
