; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/sha256.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_check_state = type { %union.anon, %union.anon.0 }
%union.anon = type { [8 x i64] }
%union.anon.0 = type { %struct.anon }
%struct.anon = type { [8 x i32], i64 }

@lzma_sha256_init.s = internal constant [8 x i32] [i32 1779033703, i32 -1150833019, i32 1013904242, i32 -1521486534, i32 1359893119, i32 -1694144372, i32 528734635, i32 1541459225], align 16
@SHA256_K = internal constant [64 x i32] [i32 1116352408, i32 1899447441, i32 -1245643825, i32 -373957723, i32 961987163, i32 1508970993, i32 -1841331548, i32 -1424204075, i32 -670586216, i32 310598401, i32 607225278, i32 1426881987, i32 1925078388, i32 -2132889090, i32 -1680079193, i32 -1046744716, i32 -459576895, i32 -272742522, i32 264347078, i32 604807628, i32 770255983, i32 1249150122, i32 1555081692, i32 1996064986, i32 -1740746414, i32 -1473132947, i32 -1341970488, i32 -1084653625, i32 -958395405, i32 -710438585, i32 113926993, i32 338241895, i32 666307205, i32 773529912, i32 1294757372, i32 1396182291, i32 1695183700, i32 1986661051, i32 -2117940946, i32 -1838011259, i32 -1564481375, i32 -1474664885, i32 -1035236496, i32 -949202525, i32 -778901479, i32 -694614492, i32 -200395387, i32 275423344, i32 430227734, i32 506948616, i32 659060556, i32 883997877, i32 958139571, i32 1322822218, i32 1537002063, i32 1747873779, i32 1955562222, i32 2024104815, i32 -2067236844, i32 -1933114872, i32 -1866530822, i32 -1538233109, i32 -1090935817, i32 -965641998], align 16

; Function Attrs: nounwind uwtable
define void @lzma_sha256_init(%struct.lzma_check_state* %check) #0 !dbg !4 {
entry:
  %check.addr = alloca %struct.lzma_check_state*, align 8
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !68, metadata !69), !dbg !70
  %0 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !71
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %0, i32 0, i32 1, !dbg !72
  %sha256 = bitcast %union.anon.0* %state to %struct.anon*, !dbg !73
  %state1 = getelementptr inbounds %struct.anon, %struct.anon* %sha256, i32 0, i32 0, !dbg !74
  %arraydecay = getelementptr inbounds [8 x i32], [8 x i32]* %state1, i32 0, i32 0, !dbg !75
  %1 = bitcast i32* %arraydecay to i8*, !dbg !75
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %1, i8* bitcast ([8 x i32]* @lzma_sha256_init.s to i8*), i64 32, i32 8, i1 false), !dbg !75
  %2 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !76
  %state2 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %2, i32 0, i32 1, !dbg !77
  %sha2563 = bitcast %union.anon.0* %state2 to %struct.anon*, !dbg !78
  %size = getelementptr inbounds %struct.anon, %struct.anon* %sha2563, i32 0, i32 1, !dbg !79
  store i64 0, i64* %size, align 8, !dbg !80
  ret void, !dbg !81
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define void @lzma_sha256_update(i8* %buf, i64 %size, %struct.lzma_check_state* %check) #0 !dbg !45 {
entry:
  %buf.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %check.addr = alloca %struct.lzma_check_state*, align 8
  %copy_start = alloca i64, align 8
  %copy_size = alloca i64, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !82, metadata !69), !dbg !83
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !84, metadata !69), !dbg !85
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !86, metadata !69), !dbg !87
  br label %while.cond, !dbg !88

while.cond:                                       ; preds = %if.end14, %entry
  %0 = load i64, i64* %size.addr, align 8, !dbg !89
  %cmp = icmp ugt i64 %0, 0, !dbg !91
  br i1 %cmp, label %while.body, label %while.end, !dbg !92

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %copy_start, metadata !93, metadata !69), !dbg !96
  %1 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !97
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %1, i32 0, i32 1, !dbg !98
  %sha256 = bitcast %union.anon.0* %state to %struct.anon*, !dbg !99
  %size1 = getelementptr inbounds %struct.anon, %struct.anon* %sha256, i32 0, i32 1, !dbg !100
  %2 = load i64, i64* %size1, align 8, !dbg !100
  %and = and i64 %2, 63, !dbg !101
  store i64 %and, i64* %copy_start, align 8, !dbg !96
  call void @llvm.dbg.declare(metadata i64* %copy_size, metadata !102, metadata !69), !dbg !103
  %3 = load i64, i64* %copy_start, align 8, !dbg !104
  %sub = sub i64 64, %3, !dbg !105
  store i64 %sub, i64* %copy_size, align 8, !dbg !103
  %4 = load i64, i64* %copy_size, align 8, !dbg !106
  %5 = load i64, i64* %size.addr, align 8, !dbg !108
  %cmp2 = icmp ugt i64 %4, %5, !dbg !109
  br i1 %cmp2, label %if.then, label %if.end, !dbg !110

if.then:                                          ; preds = %while.body
  %6 = load i64, i64* %size.addr, align 8, !dbg !111
  store i64 %6, i64* %copy_size, align 8, !dbg !112
  br label %if.end, !dbg !113

if.end:                                           ; preds = %if.then, %while.body
  %7 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !114
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %7, i32 0, i32 0, !dbg !115
  %u8 = bitcast %union.anon* %buffer to [64 x i8]*, !dbg !116
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %u8, i32 0, i32 0, !dbg !114
  %8 = load i64, i64* %copy_start, align 8, !dbg !117
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 %8, !dbg !118
  %9 = load i8*, i8** %buf.addr, align 8, !dbg !119
  %10 = load i64, i64* %copy_size, align 8, !dbg !120
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %9, i64 %10, i32 1, i1 false), !dbg !121
  %11 = load i64, i64* %copy_size, align 8, !dbg !122
  %12 = load i8*, i8** %buf.addr, align 8, !dbg !123
  %add.ptr3 = getelementptr inbounds i8, i8* %12, i64 %11, !dbg !123
  store i8* %add.ptr3, i8** %buf.addr, align 8, !dbg !123
  %13 = load i64, i64* %copy_size, align 8, !dbg !124
  %14 = load i64, i64* %size.addr, align 8, !dbg !125
  %sub4 = sub i64 %14, %13, !dbg !125
  store i64 %sub4, i64* %size.addr, align 8, !dbg !125
  %15 = load i64, i64* %copy_size, align 8, !dbg !126
  %16 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !127
  %state5 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %16, i32 0, i32 1, !dbg !128
  %sha2566 = bitcast %union.anon.0* %state5 to %struct.anon*, !dbg !129
  %size7 = getelementptr inbounds %struct.anon, %struct.anon* %sha2566, i32 0, i32 1, !dbg !130
  %17 = load i64, i64* %size7, align 8, !dbg !131
  %add = add i64 %17, %15, !dbg !131
  store i64 %add, i64* %size7, align 8, !dbg !131
  %18 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !132
  %state8 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %18, i32 0, i32 1, !dbg !134
  %sha2569 = bitcast %union.anon.0* %state8 to %struct.anon*, !dbg !135
  %size10 = getelementptr inbounds %struct.anon, %struct.anon* %sha2569, i32 0, i32 1, !dbg !136
  %19 = load i64, i64* %size10, align 8, !dbg !136
  %and11 = and i64 %19, 63, !dbg !137
  %cmp12 = icmp eq i64 %and11, 0, !dbg !138
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !139

if.then13:                                        ; preds = %if.end
  %20 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !140
  call void @process(%struct.lzma_check_state* %20), !dbg !141
  br label %if.end14, !dbg !141

if.end14:                                         ; preds = %if.then13, %if.end
  br label %while.cond, !dbg !142

while.end:                                        ; preds = %while.cond
  ret void, !dbg !144
}

; Function Attrs: nounwind uwtable
define internal void @process(%struct.lzma_check_state* %check) #0 !dbg !53 {
entry:
  %check.addr = alloca %struct.lzma_check_state*, align 8
  %data = alloca [16 x i32], align 16
  %i = alloca i64, align 8
  %__v = alloca i32, align 4
  %__x = alloca i32, align 4
  %tmp = alloca i32, align 4
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !145, metadata !69), !dbg !146
  call void @llvm.dbg.declare(metadata [16 x i32]* %data, metadata !147, metadata !69), !dbg !148
  call void @llvm.dbg.declare(metadata i64* %i, metadata !149, metadata !69), !dbg !150
  store i64 0, i64* %i, align 8, !dbg !151
  br label %for.cond, !dbg !153

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8, !dbg !154
  %cmp = icmp ult i64 %0, 16, !dbg !157
  br i1 %cmp, label %for.body, label %for.end, !dbg !158

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %__v, metadata !159, metadata !69), !dbg !161
  call void @llvm.dbg.declare(metadata i32* %__x, metadata !162, metadata !69), !dbg !161
  %1 = load i64, i64* %i, align 8, !dbg !161
  %2 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !161
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %2, i32 0, i32 0, !dbg !161
  %u32 = bitcast %union.anon* %buffer to [16 x i32]*, !dbg !161
  %arrayidx = getelementptr inbounds [16 x i32], [16 x i32]* %u32, i64 0, i64 %1, !dbg !161
  %3 = load i32, i32* %arrayidx, align 4, !dbg !161
  store i32 %3, i32* %__x, align 4, !dbg !161
  %4 = load i32, i32* %__x, align 4, !dbg !163
  %5 = call i32 asm "bswap $0", "=r,0,~{dirflag},~{fpsr},~{flags}"(i32 %4) #1, !dbg !163, !srcloc !165
  store i32 %5, i32* %__v, align 4, !dbg !163
  %6 = load i32, i32* %__v, align 4, !dbg !161
  store i32 %6, i32* %tmp, align 4, !dbg !163
  %7 = load i32, i32* %tmp, align 4, !dbg !161
  %8 = load i64, i64* %i, align 8, !dbg !166
  %arrayidx1 = getelementptr inbounds [16 x i32], [16 x i32]* %data, i64 0, i64 %8, !dbg !167
  store i32 %7, i32* %arrayidx1, align 4, !dbg !168
  br label %for.inc, !dbg !167

for.inc:                                          ; preds = %for.body
  %9 = load i64, i64* %i, align 8, !dbg !169
  %inc = add i64 %9, 1, !dbg !169
  store i64 %inc, i64* %i, align 8, !dbg !169
  br label %for.cond, !dbg !171

for.end:                                          ; preds = %for.cond
  %10 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !172
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %10, i32 0, i32 1, !dbg !173
  %sha256 = bitcast %union.anon.0* %state to %struct.anon*, !dbg !174
  %state2 = getelementptr inbounds %struct.anon, %struct.anon* %sha256, i32 0, i32 0, !dbg !175
  %arraydecay = getelementptr inbounds [8 x i32], [8 x i32]* %state2, i32 0, i32 0, !dbg !172
  %arraydecay3 = getelementptr inbounds [16 x i32], [16 x i32]* %data, i32 0, i32 0, !dbg !176
  call void @transform(i32* %arraydecay, i32* %arraydecay3), !dbg !177
  ret void, !dbg !178
}

; Function Attrs: nounwind uwtable
define void @lzma_sha256_finish(%struct.lzma_check_state* %check) #0 !dbg !52 {
entry:
  %check.addr = alloca %struct.lzma_check_state*, align 8
  %i = alloca i64, align 8
  %pos = alloca i64, align 8
  %__v = alloca i64, align 8
  %__x = alloca i64, align 8
  %tmp = alloca i64, align 8
  %__v16 = alloca i32, align 4
  %__x18 = alloca i32, align 4
  %tmp23 = alloca i32, align 4
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !179, metadata !69), !dbg !180
  call void @llvm.dbg.declare(metadata i64* %i, metadata !181, metadata !69), !dbg !182
  call void @llvm.dbg.declare(metadata i64* %pos, metadata !183, metadata !69), !dbg !184
  %0 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !185
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %0, i32 0, i32 1, !dbg !186
  %sha256 = bitcast %union.anon.0* %state to %struct.anon*, !dbg !187
  %size = getelementptr inbounds %struct.anon, %struct.anon* %sha256, i32 0, i32 1, !dbg !188
  %1 = load i64, i64* %size, align 8, !dbg !188
  %and = and i64 %1, 63, !dbg !189
  store i64 %and, i64* %pos, align 8, !dbg !184
  %2 = load i64, i64* %pos, align 8, !dbg !190
  %inc = add i64 %2, 1, !dbg !190
  store i64 %inc, i64* %pos, align 8, !dbg !190
  %3 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !191
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %3, i32 0, i32 0, !dbg !192
  %u8 = bitcast %union.anon* %buffer to [64 x i8]*, !dbg !193
  %arrayidx = getelementptr inbounds [64 x i8], [64 x i8]* %u8, i64 0, i64 %2, !dbg !191
  store i8 -128, i8* %arrayidx, align 1, !dbg !194
  br label %while.cond, !dbg !195

while.cond:                                       ; preds = %if.end, %entry
  %4 = load i64, i64* %pos, align 8, !dbg !196
  %cmp = icmp ne i64 %4, 56, !dbg !198
  br i1 %cmp, label %while.body, label %while.end, !dbg !199

while.body:                                       ; preds = %while.cond
  %5 = load i64, i64* %pos, align 8, !dbg !200
  %cmp1 = icmp eq i64 %5, 64, !dbg !203
  br i1 %cmp1, label %if.then, label %if.end, !dbg !204

if.then:                                          ; preds = %while.body
  %6 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !205
  call void @process(%struct.lzma_check_state* %6), !dbg !207
  store i64 0, i64* %pos, align 8, !dbg !208
  br label %if.end, !dbg !209

if.end:                                           ; preds = %if.then, %while.body
  %7 = load i64, i64* %pos, align 8, !dbg !210
  %inc2 = add i64 %7, 1, !dbg !210
  store i64 %inc2, i64* %pos, align 8, !dbg !210
  %8 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !211
  %buffer3 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %8, i32 0, i32 0, !dbg !212
  %u84 = bitcast %union.anon* %buffer3 to [64 x i8]*, !dbg !213
  %arrayidx5 = getelementptr inbounds [64 x i8], [64 x i8]* %u84, i64 0, i64 %7, !dbg !211
  store i8 0, i8* %arrayidx5, align 1, !dbg !214
  br label %while.cond, !dbg !215

while.end:                                        ; preds = %while.cond
  %9 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !217
  %state6 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %9, i32 0, i32 1, !dbg !218
  %sha2567 = bitcast %union.anon.0* %state6 to %struct.anon*, !dbg !219
  %size8 = getelementptr inbounds %struct.anon, %struct.anon* %sha2567, i32 0, i32 1, !dbg !220
  %10 = load i64, i64* %size8, align 8, !dbg !221
  %mul = mul i64 %10, 8, !dbg !221
  store i64 %mul, i64* %size8, align 8, !dbg !221
  call void @llvm.dbg.declare(metadata i64* %__v, metadata !222, metadata !69), !dbg !226
  call void @llvm.dbg.declare(metadata i64* %__x, metadata !227, metadata !69), !dbg !226
  %11 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !226
  %state9 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %11, i32 0, i32 1, !dbg !226
  %sha25610 = bitcast %union.anon.0* %state9 to %struct.anon*, !dbg !226
  %size11 = getelementptr inbounds %struct.anon, %struct.anon* %sha25610, i32 0, i32 1, !dbg !226
  %12 = load i64, i64* %size11, align 8, !dbg !226
  store i64 %12, i64* %__x, align 8, !dbg !226
  %13 = load i64, i64* %__x, align 8, !dbg !228
  %14 = call i64 asm "bswap ${0:q}", "=r,0,~{dirflag},~{fpsr},~{flags}"(i64 %13) #1, !dbg !228, !srcloc !230
  store i64 %14, i64* %__v, align 8, !dbg !228
  %15 = load i64, i64* %__v, align 8, !dbg !226
  store i64 %15, i64* %tmp, align 8, !dbg !228
  %16 = load i64, i64* %tmp, align 8, !dbg !226
  %17 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !231
  %buffer12 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %17, i32 0, i32 0, !dbg !232
  %u64 = bitcast %union.anon* %buffer12 to [8 x i64]*, !dbg !233
  %arrayidx13 = getelementptr inbounds [8 x i64], [8 x i64]* %u64, i64 0, i64 7, !dbg !231
  store i64 %16, i64* %arrayidx13, align 8, !dbg !234
  %18 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !235
  call void @process(%struct.lzma_check_state* %18), !dbg !236
  store i64 0, i64* %i, align 8, !dbg !237
  br label %for.cond, !dbg !239

for.cond:                                         ; preds = %for.inc, %while.end
  %19 = load i64, i64* %i, align 8, !dbg !240
  %cmp14 = icmp ult i64 %19, 8, !dbg !243
  br i1 %cmp14, label %for.body, label %for.end, !dbg !244

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %__v16, metadata !245, metadata !69), !dbg !247
  call void @llvm.dbg.declare(metadata i32* %__x18, metadata !248, metadata !69), !dbg !247
  %20 = load i64, i64* %i, align 8, !dbg !247
  %21 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !247
  %state19 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %21, i32 0, i32 1, !dbg !247
  %sha25620 = bitcast %union.anon.0* %state19 to %struct.anon*, !dbg !247
  %state21 = getelementptr inbounds %struct.anon, %struct.anon* %sha25620, i32 0, i32 0, !dbg !247
  %arrayidx22 = getelementptr inbounds [8 x i32], [8 x i32]* %state21, i64 0, i64 %20, !dbg !247
  %22 = load i32, i32* %arrayidx22, align 4, !dbg !247
  store i32 %22, i32* %__x18, align 4, !dbg !247
  %23 = load i32, i32* %__x18, align 4, !dbg !249
  %24 = call i32 asm "bswap $0", "=r,0,~{dirflag},~{fpsr},~{flags}"(i32 %23) #1, !dbg !249, !srcloc !251
  store i32 %24, i32* %__v16, align 4, !dbg !249
  %25 = load i32, i32* %__v16, align 4, !dbg !247
  store i32 %25, i32* %tmp23, align 4, !dbg !249
  %26 = load i32, i32* %tmp23, align 4, !dbg !247
  %27 = load i64, i64* %i, align 8, !dbg !252
  %28 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !253
  %buffer24 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %28, i32 0, i32 0, !dbg !254
  %u32 = bitcast %union.anon* %buffer24 to [16 x i32]*, !dbg !255
  %arrayidx25 = getelementptr inbounds [16 x i32], [16 x i32]* %u32, i64 0, i64 %27, !dbg !253
  store i32 %26, i32* %arrayidx25, align 4, !dbg !256
  br label %for.inc, !dbg !253

for.inc:                                          ; preds = %for.body
  %29 = load i64, i64* %i, align 8, !dbg !257
  %inc26 = add i64 %29, 1, !dbg !257
  store i64 %inc26, i64* %i, align 8, !dbg !257
  br label %for.cond, !dbg !259

for.end:                                          ; preds = %for.cond
  ret void, !dbg !260
}

; Function Attrs: nounwind uwtable
define internal void @transform(i32* %state, i32* %data) #0 !dbg !54 {
entry:
  %state.addr = alloca i32*, align 8
  %data.addr = alloca i32*, align 8
  %W = alloca [16 x i32], align 16
  %T = alloca [8 x i32], align 16
  %j = alloca i32, align 4
  store i32* %state, i32** %state.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %state.addr, metadata !261, metadata !69), !dbg !262
  store i32* %data, i32** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %data.addr, metadata !263, metadata !69), !dbg !264
  call void @llvm.dbg.declare(metadata [16 x i32]* %W, metadata !265, metadata !69), !dbg !266
  call void @llvm.dbg.declare(metadata [8 x i32]* %T, metadata !267, metadata !69), !dbg !268
  call void @llvm.dbg.declare(metadata i32* %j, metadata !269, metadata !69), !dbg !270
  %arraydecay = getelementptr inbounds [8 x i32], [8 x i32]* %T, i32 0, i32 0, !dbg !271
  %0 = bitcast i32* %arraydecay to i8*, !dbg !271
  %1 = load i32*, i32** %state.addr, align 8, !dbg !272
  %2 = bitcast i32* %1 to i8*, !dbg !271
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* %2, i64 32, i32 4, i1 false), !dbg !271
  store i32 0, i32* %j, align 4, !dbg !273
  br label %for.cond, !dbg !275

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i32, i32* %j, align 4, !dbg !276
  %cmp = icmp ult i32 %3, 64, !dbg !279
  br i1 %cmp, label %for.body, label %for.end, !dbg !280

for.body:                                         ; preds = %for.cond
  %arrayidx = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %4 = load i32, i32* %arrayidx, align 16, !dbg !281
  %shr = lshr i32 %4, 6, !dbg !281
  %arrayidx1 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %5 = load i32, i32* %arrayidx1, align 16, !dbg !281
  %shl = shl i32 %5, 26, !dbg !281
  %or = or i32 %shr, %shl, !dbg !281
  %arrayidx2 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %6 = load i32, i32* %arrayidx2, align 16, !dbg !281
  %shr3 = lshr i32 %6, 11, !dbg !281
  %arrayidx4 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %7 = load i32, i32* %arrayidx4, align 16, !dbg !281
  %shl5 = shl i32 %7, 21, !dbg !281
  %or6 = or i32 %shr3, %shl5, !dbg !281
  %xor = xor i32 %or, %or6, !dbg !281
  %arrayidx7 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %8 = load i32, i32* %arrayidx7, align 16, !dbg !281
  %shr8 = lshr i32 %8, 25, !dbg !281
  %arrayidx9 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %9 = load i32, i32* %arrayidx9, align 16, !dbg !281
  %shl10 = shl i32 %9, 7, !dbg !281
  %or11 = or i32 %shr8, %shl10, !dbg !281
  %xor12 = xor i32 %xor, %or11, !dbg !281
  %arrayidx13 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !281
  %10 = load i32, i32* %arrayidx13, align 8, !dbg !281
  %arrayidx14 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !281
  %11 = load i32, i32* %arrayidx14, align 16, !dbg !281
  %arrayidx15 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !281
  %12 = load i32, i32* %arrayidx15, align 4, !dbg !281
  %arrayidx16 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !281
  %13 = load i32, i32* %arrayidx16, align 8, !dbg !281
  %xor17 = xor i32 %12, %13, !dbg !281
  %and = and i32 %11, %xor17, !dbg !281
  %xor18 = xor i32 %10, %and, !dbg !281
  %add = add i32 %xor12, %xor18, !dbg !281
  %14 = load i32, i32* %j, align 4, !dbg !281
  %add19 = add i32 0, %14, !dbg !281
  %idxprom = zext i32 %add19 to i64, !dbg !281
  %arrayidx20 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom, !dbg !281
  %15 = load i32, i32* %arrayidx20, align 4, !dbg !281
  %add21 = add i32 %add, %15, !dbg !281
  %16 = load i32, i32* %j, align 4, !dbg !281
  %tobool = icmp ne i32 %16, 0, !dbg !281
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !281

cond.true:                                        ; preds = %for.body
  %arrayidx22 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !283
  %17 = load i32, i32* %arrayidx22, align 8, !dbg !283
  %shr23 = lshr i32 %17, 17, !dbg !283
  %arrayidx24 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !283
  %18 = load i32, i32* %arrayidx24, align 8, !dbg !283
  %shl25 = shl i32 %18, 15, !dbg !283
  %or26 = or i32 %shr23, %shl25, !dbg !283
  %arrayidx27 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !283
  %19 = load i32, i32* %arrayidx27, align 8, !dbg !283
  %shr28 = lshr i32 %19, 19, !dbg !283
  %arrayidx29 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !283
  %20 = load i32, i32* %arrayidx29, align 8, !dbg !283
  %shl30 = shl i32 %20, 13, !dbg !283
  %or31 = or i32 %shr28, %shl30, !dbg !283
  %xor32 = xor i32 %or26, %or31, !dbg !283
  %arrayidx33 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !283
  %21 = load i32, i32* %arrayidx33, align 8, !dbg !283
  %shr34 = lshr i32 %21, 10, !dbg !283
  %xor35 = xor i32 %xor32, %shr34, !dbg !283
  %arrayidx36 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !283
  %22 = load i32, i32* %arrayidx36, align 4, !dbg !283
  %add37 = add i32 %xor35, %22, !dbg !283
  %arrayidx38 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !283
  %23 = load i32, i32* %arrayidx38, align 4, !dbg !283
  %shr39 = lshr i32 %23, 7, !dbg !283
  %arrayidx40 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !283
  %24 = load i32, i32* %arrayidx40, align 4, !dbg !283
  %shl41 = shl i32 %24, 25, !dbg !283
  %or42 = or i32 %shr39, %shl41, !dbg !283
  %arrayidx43 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !283
  %25 = load i32, i32* %arrayidx43, align 4, !dbg !283
  %shr44 = lshr i32 %25, 18, !dbg !283
  %arrayidx45 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !283
  %26 = load i32, i32* %arrayidx45, align 4, !dbg !283
  %shl46 = shl i32 %26, 14, !dbg !283
  %or47 = or i32 %shr44, %shl46, !dbg !283
  %xor48 = xor i32 %or42, %or47, !dbg !283
  %arrayidx49 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !283
  %27 = load i32, i32* %arrayidx49, align 4, !dbg !283
  %shr50 = lshr i32 %27, 3, !dbg !283
  %xor51 = xor i32 %xor48, %shr50, !dbg !283
  %add52 = add i32 %add37, %xor51, !dbg !283
  %arrayidx53 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !283
  %28 = load i32, i32* %arrayidx53, align 16, !dbg !283
  %add54 = add i32 %28, %add52, !dbg !283
  store i32 %add54, i32* %arrayidx53, align 16, !dbg !283
  br label %cond.end, !dbg !283

cond.false:                                       ; preds = %for.body
  %29 = load i32*, i32** %data.addr, align 8, !dbg !285
  %arrayidx55 = getelementptr inbounds i32, i32* %29, i64 0, !dbg !285
  %30 = load i32, i32* %arrayidx55, align 4, !dbg !285
  %arrayidx56 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !285
  store i32 %30, i32* %arrayidx56, align 16, !dbg !285
  br label %cond.end, !dbg !285

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %add54, %cond.true ], [ %30, %cond.false ], !dbg !287
  %add57 = add i32 %add21, %cond, !dbg !287
  %arrayidx58 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !287
  %31 = load i32, i32* %arrayidx58, align 4, !dbg !287
  %add59 = add i32 %31, %add57, !dbg !287
  store i32 %add59, i32* %arrayidx58, align 4, !dbg !287
  %arrayidx60 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !287
  %32 = load i32, i32* %arrayidx60, align 4, !dbg !287
  %arrayidx61 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !287
  %33 = load i32, i32* %arrayidx61, align 4, !dbg !287
  %add62 = add i32 %33, %32, !dbg !287
  store i32 %add62, i32* %arrayidx61, align 4, !dbg !287
  %arrayidx63 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %34 = load i32, i32* %arrayidx63, align 16, !dbg !287
  %shr64 = lshr i32 %34, 2, !dbg !287
  %arrayidx65 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %35 = load i32, i32* %arrayidx65, align 16, !dbg !287
  %shl66 = shl i32 %35, 30, !dbg !287
  %or67 = or i32 %shr64, %shl66, !dbg !287
  %arrayidx68 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %36 = load i32, i32* %arrayidx68, align 16, !dbg !287
  %shr69 = lshr i32 %36, 13, !dbg !287
  %arrayidx70 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %37 = load i32, i32* %arrayidx70, align 16, !dbg !287
  %shl71 = shl i32 %37, 19, !dbg !287
  %or72 = or i32 %shr69, %shl71, !dbg !287
  %xor73 = xor i32 %or67, %or72, !dbg !287
  %arrayidx74 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %38 = load i32, i32* %arrayidx74, align 16, !dbg !287
  %shr75 = lshr i32 %38, 22, !dbg !287
  %arrayidx76 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %39 = load i32, i32* %arrayidx76, align 16, !dbg !287
  %shl77 = shl i32 %39, 10, !dbg !287
  %or78 = or i32 %shr75, %shl77, !dbg !287
  %xor79 = xor i32 %xor73, %or78, !dbg !287
  %arrayidx80 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %40 = load i32, i32* %arrayidx80, align 16, !dbg !287
  %arrayidx81 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !287
  %41 = load i32, i32* %arrayidx81, align 4, !dbg !287
  %and82 = and i32 %40, %41, !dbg !287
  %arrayidx83 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !287
  %42 = load i32, i32* %arrayidx83, align 8, !dbg !287
  %arrayidx84 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !287
  %43 = load i32, i32* %arrayidx84, align 16, !dbg !287
  %arrayidx85 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !287
  %44 = load i32, i32* %arrayidx85, align 4, !dbg !287
  %or86 = or i32 %43, %44, !dbg !287
  %and87 = and i32 %42, %or86, !dbg !287
  %or88 = or i32 %and82, %and87, !dbg !287
  %add89 = add i32 %xor79, %or88, !dbg !287
  %arrayidx90 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !287
  %45 = load i32, i32* %arrayidx90, align 4, !dbg !287
  %add91 = add i32 %45, %add89, !dbg !287
  store i32 %add91, i32* %arrayidx90, align 4, !dbg !287
  %arrayidx92 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %46 = load i32, i32* %arrayidx92, align 4, !dbg !289
  %shr93 = lshr i32 %46, 6, !dbg !289
  %arrayidx94 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %47 = load i32, i32* %arrayidx94, align 4, !dbg !289
  %shl95 = shl i32 %47, 26, !dbg !289
  %or96 = or i32 %shr93, %shl95, !dbg !289
  %arrayidx97 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %48 = load i32, i32* %arrayidx97, align 4, !dbg !289
  %shr98 = lshr i32 %48, 11, !dbg !289
  %arrayidx99 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %49 = load i32, i32* %arrayidx99, align 4, !dbg !289
  %shl100 = shl i32 %49, 21, !dbg !289
  %or101 = or i32 %shr98, %shl100, !dbg !289
  %xor102 = xor i32 %or96, %or101, !dbg !289
  %arrayidx103 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %50 = load i32, i32* %arrayidx103, align 4, !dbg !289
  %shr104 = lshr i32 %50, 25, !dbg !289
  %arrayidx105 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %51 = load i32, i32* %arrayidx105, align 4, !dbg !289
  %shl106 = shl i32 %51, 7, !dbg !289
  %or107 = or i32 %shr104, %shl106, !dbg !289
  %xor108 = xor i32 %xor102, %or107, !dbg !289
  %arrayidx109 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !289
  %52 = load i32, i32* %arrayidx109, align 4, !dbg !289
  %arrayidx110 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !289
  %53 = load i32, i32* %arrayidx110, align 4, !dbg !289
  %arrayidx111 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !289
  %54 = load i32, i32* %arrayidx111, align 16, !dbg !289
  %arrayidx112 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !289
  %55 = load i32, i32* %arrayidx112, align 4, !dbg !289
  %xor113 = xor i32 %54, %55, !dbg !289
  %and114 = and i32 %53, %xor113, !dbg !289
  %xor115 = xor i32 %52, %and114, !dbg !289
  %add116 = add i32 %xor108, %xor115, !dbg !289
  %56 = load i32, i32* %j, align 4, !dbg !289
  %add117 = add i32 1, %56, !dbg !289
  %idxprom118 = zext i32 %add117 to i64, !dbg !289
  %arrayidx119 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom118, !dbg !289
  %57 = load i32, i32* %arrayidx119, align 4, !dbg !289
  %add120 = add i32 %add116, %57, !dbg !289
  %58 = load i32, i32* %j, align 4, !dbg !289
  %tobool121 = icmp ne i32 %58, 0, !dbg !289
  br i1 %tobool121, label %cond.true122, label %cond.false156, !dbg !289

cond.true122:                                     ; preds = %cond.end
  %arrayidx123 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !290
  %59 = load i32, i32* %arrayidx123, align 4, !dbg !290
  %shr124 = lshr i32 %59, 17, !dbg !290
  %arrayidx125 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !290
  %60 = load i32, i32* %arrayidx125, align 4, !dbg !290
  %shl126 = shl i32 %60, 15, !dbg !290
  %or127 = or i32 %shr124, %shl126, !dbg !290
  %arrayidx128 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !290
  %61 = load i32, i32* %arrayidx128, align 4, !dbg !290
  %shr129 = lshr i32 %61, 19, !dbg !290
  %arrayidx130 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !290
  %62 = load i32, i32* %arrayidx130, align 4, !dbg !290
  %shl131 = shl i32 %62, 13, !dbg !290
  %or132 = or i32 %shr129, %shl131, !dbg !290
  %xor133 = xor i32 %or127, %or132, !dbg !290
  %arrayidx134 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !290
  %63 = load i32, i32* %arrayidx134, align 4, !dbg !290
  %shr135 = lshr i32 %63, 10, !dbg !290
  %xor136 = xor i32 %xor133, %shr135, !dbg !290
  %arrayidx137 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !290
  %64 = load i32, i32* %arrayidx137, align 8, !dbg !290
  %add138 = add i32 %xor136, %64, !dbg !290
  %arrayidx139 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !290
  %65 = load i32, i32* %arrayidx139, align 8, !dbg !290
  %shr140 = lshr i32 %65, 7, !dbg !290
  %arrayidx141 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !290
  %66 = load i32, i32* %arrayidx141, align 8, !dbg !290
  %shl142 = shl i32 %66, 25, !dbg !290
  %or143 = or i32 %shr140, %shl142, !dbg !290
  %arrayidx144 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !290
  %67 = load i32, i32* %arrayidx144, align 8, !dbg !290
  %shr145 = lshr i32 %67, 18, !dbg !290
  %arrayidx146 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !290
  %68 = load i32, i32* %arrayidx146, align 8, !dbg !290
  %shl147 = shl i32 %68, 14, !dbg !290
  %or148 = or i32 %shr145, %shl147, !dbg !290
  %xor149 = xor i32 %or143, %or148, !dbg !290
  %arrayidx150 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !290
  %69 = load i32, i32* %arrayidx150, align 8, !dbg !290
  %shr151 = lshr i32 %69, 3, !dbg !290
  %xor152 = xor i32 %xor149, %shr151, !dbg !290
  %add153 = add i32 %add138, %xor152, !dbg !290
  %arrayidx154 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !290
  %70 = load i32, i32* %arrayidx154, align 4, !dbg !290
  %add155 = add i32 %70, %add153, !dbg !290
  store i32 %add155, i32* %arrayidx154, align 4, !dbg !290
  br label %cond.end159, !dbg !290

cond.false156:                                    ; preds = %cond.end
  %71 = load i32*, i32** %data.addr, align 8, !dbg !292
  %arrayidx157 = getelementptr inbounds i32, i32* %71, i64 1, !dbg !292
  %72 = load i32, i32* %arrayidx157, align 4, !dbg !292
  %arrayidx158 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !292
  store i32 %72, i32* %arrayidx158, align 4, !dbg !292
  br label %cond.end159, !dbg !292

cond.end159:                                      ; preds = %cond.false156, %cond.true122
  %cond160 = phi i32 [ %add155, %cond.true122 ], [ %72, %cond.false156 ], !dbg !294
  %add161 = add i32 %add120, %cond160, !dbg !294
  %arrayidx162 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !294
  %73 = load i32, i32* %arrayidx162, align 8, !dbg !294
  %add163 = add i32 %73, %add161, !dbg !294
  store i32 %add163, i32* %arrayidx162, align 8, !dbg !294
  %arrayidx164 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !294
  %74 = load i32, i32* %arrayidx164, align 8, !dbg !294
  %arrayidx165 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !294
  %75 = load i32, i32* %arrayidx165, align 8, !dbg !294
  %add166 = add i32 %75, %74, !dbg !294
  store i32 %add166, i32* %arrayidx165, align 8, !dbg !294
  %arrayidx167 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %76 = load i32, i32* %arrayidx167, align 4, !dbg !294
  %shr168 = lshr i32 %76, 2, !dbg !294
  %arrayidx169 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %77 = load i32, i32* %arrayidx169, align 4, !dbg !294
  %shl170 = shl i32 %77, 30, !dbg !294
  %or171 = or i32 %shr168, %shl170, !dbg !294
  %arrayidx172 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %78 = load i32, i32* %arrayidx172, align 4, !dbg !294
  %shr173 = lshr i32 %78, 13, !dbg !294
  %arrayidx174 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %79 = load i32, i32* %arrayidx174, align 4, !dbg !294
  %shl175 = shl i32 %79, 19, !dbg !294
  %or176 = or i32 %shr173, %shl175, !dbg !294
  %xor177 = xor i32 %or171, %or176, !dbg !294
  %arrayidx178 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %80 = load i32, i32* %arrayidx178, align 4, !dbg !294
  %shr179 = lshr i32 %80, 22, !dbg !294
  %arrayidx180 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %81 = load i32, i32* %arrayidx180, align 4, !dbg !294
  %shl181 = shl i32 %81, 10, !dbg !294
  %or182 = or i32 %shr179, %shl181, !dbg !294
  %xor183 = xor i32 %xor177, %or182, !dbg !294
  %arrayidx184 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %82 = load i32, i32* %arrayidx184, align 4, !dbg !294
  %arrayidx185 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !294
  %83 = load i32, i32* %arrayidx185, align 16, !dbg !294
  %and186 = and i32 %82, %83, !dbg !294
  %arrayidx187 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !294
  %84 = load i32, i32* %arrayidx187, align 4, !dbg !294
  %arrayidx188 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !294
  %85 = load i32, i32* %arrayidx188, align 4, !dbg !294
  %arrayidx189 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !294
  %86 = load i32, i32* %arrayidx189, align 16, !dbg !294
  %or190 = or i32 %85, %86, !dbg !294
  %and191 = and i32 %84, %or190, !dbg !294
  %or192 = or i32 %and186, %and191, !dbg !294
  %add193 = add i32 %xor183, %or192, !dbg !294
  %arrayidx194 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !294
  %87 = load i32, i32* %arrayidx194, align 8, !dbg !294
  %add195 = add i32 %87, %add193, !dbg !294
  store i32 %add195, i32* %arrayidx194, align 8, !dbg !294
  %arrayidx196 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %88 = load i32, i32* %arrayidx196, align 8, !dbg !296
  %shr197 = lshr i32 %88, 6, !dbg !296
  %arrayidx198 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %89 = load i32, i32* %arrayidx198, align 8, !dbg !296
  %shl199 = shl i32 %89, 26, !dbg !296
  %or200 = or i32 %shr197, %shl199, !dbg !296
  %arrayidx201 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %90 = load i32, i32* %arrayidx201, align 8, !dbg !296
  %shr202 = lshr i32 %90, 11, !dbg !296
  %arrayidx203 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %91 = load i32, i32* %arrayidx203, align 8, !dbg !296
  %shl204 = shl i32 %91, 21, !dbg !296
  %or205 = or i32 %shr202, %shl204, !dbg !296
  %xor206 = xor i32 %or200, %or205, !dbg !296
  %arrayidx207 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %92 = load i32, i32* %arrayidx207, align 8, !dbg !296
  %shr208 = lshr i32 %92, 25, !dbg !296
  %arrayidx209 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %93 = load i32, i32* %arrayidx209, align 8, !dbg !296
  %shl210 = shl i32 %93, 7, !dbg !296
  %or211 = or i32 %shr208, %shl210, !dbg !296
  %xor212 = xor i32 %xor206, %or211, !dbg !296
  %arrayidx213 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !296
  %94 = load i32, i32* %arrayidx213, align 16, !dbg !296
  %arrayidx214 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !296
  %95 = load i32, i32* %arrayidx214, align 8, !dbg !296
  %arrayidx215 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !296
  %96 = load i32, i32* %arrayidx215, align 4, !dbg !296
  %arrayidx216 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !296
  %97 = load i32, i32* %arrayidx216, align 16, !dbg !296
  %xor217 = xor i32 %96, %97, !dbg !296
  %and218 = and i32 %95, %xor217, !dbg !296
  %xor219 = xor i32 %94, %and218, !dbg !296
  %add220 = add i32 %xor212, %xor219, !dbg !296
  %98 = load i32, i32* %j, align 4, !dbg !296
  %add221 = add i32 2, %98, !dbg !296
  %idxprom222 = zext i32 %add221 to i64, !dbg !296
  %arrayidx223 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom222, !dbg !296
  %99 = load i32, i32* %arrayidx223, align 4, !dbg !296
  %add224 = add i32 %add220, %99, !dbg !296
  %100 = load i32, i32* %j, align 4, !dbg !296
  %tobool225 = icmp ne i32 %100, 0, !dbg !296
  br i1 %tobool225, label %cond.true226, label %cond.false260, !dbg !296

cond.true226:                                     ; preds = %cond.end159
  %arrayidx227 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !297
  %101 = load i32, i32* %arrayidx227, align 16, !dbg !297
  %shr228 = lshr i32 %101, 17, !dbg !297
  %arrayidx229 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !297
  %102 = load i32, i32* %arrayidx229, align 16, !dbg !297
  %shl230 = shl i32 %102, 15, !dbg !297
  %or231 = or i32 %shr228, %shl230, !dbg !297
  %arrayidx232 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !297
  %103 = load i32, i32* %arrayidx232, align 16, !dbg !297
  %shr233 = lshr i32 %103, 19, !dbg !297
  %arrayidx234 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !297
  %104 = load i32, i32* %arrayidx234, align 16, !dbg !297
  %shl235 = shl i32 %104, 13, !dbg !297
  %or236 = or i32 %shr233, %shl235, !dbg !297
  %xor237 = xor i32 %or231, %or236, !dbg !297
  %arrayidx238 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !297
  %105 = load i32, i32* %arrayidx238, align 16, !dbg !297
  %shr239 = lshr i32 %105, 10, !dbg !297
  %xor240 = xor i32 %xor237, %shr239, !dbg !297
  %arrayidx241 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !297
  %106 = load i32, i32* %arrayidx241, align 4, !dbg !297
  %add242 = add i32 %xor240, %106, !dbg !297
  %arrayidx243 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !297
  %107 = load i32, i32* %arrayidx243, align 4, !dbg !297
  %shr244 = lshr i32 %107, 7, !dbg !297
  %arrayidx245 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !297
  %108 = load i32, i32* %arrayidx245, align 4, !dbg !297
  %shl246 = shl i32 %108, 25, !dbg !297
  %or247 = or i32 %shr244, %shl246, !dbg !297
  %arrayidx248 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !297
  %109 = load i32, i32* %arrayidx248, align 4, !dbg !297
  %shr249 = lshr i32 %109, 18, !dbg !297
  %arrayidx250 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !297
  %110 = load i32, i32* %arrayidx250, align 4, !dbg !297
  %shl251 = shl i32 %110, 14, !dbg !297
  %or252 = or i32 %shr249, %shl251, !dbg !297
  %xor253 = xor i32 %or247, %or252, !dbg !297
  %arrayidx254 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !297
  %111 = load i32, i32* %arrayidx254, align 4, !dbg !297
  %shr255 = lshr i32 %111, 3, !dbg !297
  %xor256 = xor i32 %xor253, %shr255, !dbg !297
  %add257 = add i32 %add242, %xor256, !dbg !297
  %arrayidx258 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !297
  %112 = load i32, i32* %arrayidx258, align 8, !dbg !297
  %add259 = add i32 %112, %add257, !dbg !297
  store i32 %add259, i32* %arrayidx258, align 8, !dbg !297
  br label %cond.end263, !dbg !297

cond.false260:                                    ; preds = %cond.end159
  %113 = load i32*, i32** %data.addr, align 8, !dbg !299
  %arrayidx261 = getelementptr inbounds i32, i32* %113, i64 2, !dbg !299
  %114 = load i32, i32* %arrayidx261, align 4, !dbg !299
  %arrayidx262 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !299
  store i32 %114, i32* %arrayidx262, align 8, !dbg !299
  br label %cond.end263, !dbg !299

cond.end263:                                      ; preds = %cond.false260, %cond.true226
  %cond264 = phi i32 [ %add259, %cond.true226 ], [ %114, %cond.false260 ], !dbg !301
  %add265 = add i32 %add224, %cond264, !dbg !301
  %arrayidx266 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !301
  %115 = load i32, i32* %arrayidx266, align 4, !dbg !301
  %add267 = add i32 %115, %add265, !dbg !301
  store i32 %add267, i32* %arrayidx266, align 4, !dbg !301
  %arrayidx268 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !301
  %116 = load i32, i32* %arrayidx268, align 4, !dbg !301
  %arrayidx269 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !301
  %117 = load i32, i32* %arrayidx269, align 4, !dbg !301
  %add270 = add i32 %117, %116, !dbg !301
  store i32 %add270, i32* %arrayidx269, align 4, !dbg !301
  %arrayidx271 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %118 = load i32, i32* %arrayidx271, align 8, !dbg !301
  %shr272 = lshr i32 %118, 2, !dbg !301
  %arrayidx273 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %119 = load i32, i32* %arrayidx273, align 8, !dbg !301
  %shl274 = shl i32 %119, 30, !dbg !301
  %or275 = or i32 %shr272, %shl274, !dbg !301
  %arrayidx276 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %120 = load i32, i32* %arrayidx276, align 8, !dbg !301
  %shr277 = lshr i32 %120, 13, !dbg !301
  %arrayidx278 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %121 = load i32, i32* %arrayidx278, align 8, !dbg !301
  %shl279 = shl i32 %121, 19, !dbg !301
  %or280 = or i32 %shr277, %shl279, !dbg !301
  %xor281 = xor i32 %or275, %or280, !dbg !301
  %arrayidx282 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %122 = load i32, i32* %arrayidx282, align 8, !dbg !301
  %shr283 = lshr i32 %122, 22, !dbg !301
  %arrayidx284 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %123 = load i32, i32* %arrayidx284, align 8, !dbg !301
  %shl285 = shl i32 %123, 10, !dbg !301
  %or286 = or i32 %shr283, %shl285, !dbg !301
  %xor287 = xor i32 %xor281, %or286, !dbg !301
  %arrayidx288 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %124 = load i32, i32* %arrayidx288, align 8, !dbg !301
  %arrayidx289 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !301
  %125 = load i32, i32* %arrayidx289, align 4, !dbg !301
  %and290 = and i32 %124, %125, !dbg !301
  %arrayidx291 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !301
  %126 = load i32, i32* %arrayidx291, align 16, !dbg !301
  %arrayidx292 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !301
  %127 = load i32, i32* %arrayidx292, align 8, !dbg !301
  %arrayidx293 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !301
  %128 = load i32, i32* %arrayidx293, align 4, !dbg !301
  %or294 = or i32 %127, %128, !dbg !301
  %and295 = and i32 %126, %or294, !dbg !301
  %or296 = or i32 %and290, %and295, !dbg !301
  %add297 = add i32 %xor287, %or296, !dbg !301
  %arrayidx298 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !301
  %129 = load i32, i32* %arrayidx298, align 4, !dbg !301
  %add299 = add i32 %129, %add297, !dbg !301
  store i32 %add299, i32* %arrayidx298, align 4, !dbg !301
  %arrayidx300 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %130 = load i32, i32* %arrayidx300, align 4, !dbg !303
  %shr301 = lshr i32 %130, 6, !dbg !303
  %arrayidx302 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %131 = load i32, i32* %arrayidx302, align 4, !dbg !303
  %shl303 = shl i32 %131, 26, !dbg !303
  %or304 = or i32 %shr301, %shl303, !dbg !303
  %arrayidx305 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %132 = load i32, i32* %arrayidx305, align 4, !dbg !303
  %shr306 = lshr i32 %132, 11, !dbg !303
  %arrayidx307 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %133 = load i32, i32* %arrayidx307, align 4, !dbg !303
  %shl308 = shl i32 %133, 21, !dbg !303
  %or309 = or i32 %shr306, %shl308, !dbg !303
  %xor310 = xor i32 %or304, %or309, !dbg !303
  %arrayidx311 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %134 = load i32, i32* %arrayidx311, align 4, !dbg !303
  %shr312 = lshr i32 %134, 25, !dbg !303
  %arrayidx313 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %135 = load i32, i32* %arrayidx313, align 4, !dbg !303
  %shl314 = shl i32 %135, 7, !dbg !303
  %or315 = or i32 %shr312, %shl314, !dbg !303
  %xor316 = xor i32 %xor310, %or315, !dbg !303
  %arrayidx317 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !303
  %136 = load i32, i32* %arrayidx317, align 4, !dbg !303
  %arrayidx318 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !303
  %137 = load i32, i32* %arrayidx318, align 4, !dbg !303
  %arrayidx319 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !303
  %138 = load i32, i32* %arrayidx319, align 8, !dbg !303
  %arrayidx320 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !303
  %139 = load i32, i32* %arrayidx320, align 4, !dbg !303
  %xor321 = xor i32 %138, %139, !dbg !303
  %and322 = and i32 %137, %xor321, !dbg !303
  %xor323 = xor i32 %136, %and322, !dbg !303
  %add324 = add i32 %xor316, %xor323, !dbg !303
  %140 = load i32, i32* %j, align 4, !dbg !303
  %add325 = add i32 3, %140, !dbg !303
  %idxprom326 = zext i32 %add325 to i64, !dbg !303
  %arrayidx327 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom326, !dbg !303
  %141 = load i32, i32* %arrayidx327, align 4, !dbg !303
  %add328 = add i32 %add324, %141, !dbg !303
  %142 = load i32, i32* %j, align 4, !dbg !303
  %tobool329 = icmp ne i32 %142, 0, !dbg !303
  br i1 %tobool329, label %cond.true330, label %cond.false364, !dbg !303

cond.true330:                                     ; preds = %cond.end263
  %arrayidx331 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !304
  %143 = load i32, i32* %arrayidx331, align 4, !dbg !304
  %shr332 = lshr i32 %143, 17, !dbg !304
  %arrayidx333 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !304
  %144 = load i32, i32* %arrayidx333, align 4, !dbg !304
  %shl334 = shl i32 %144, 15, !dbg !304
  %or335 = or i32 %shr332, %shl334, !dbg !304
  %arrayidx336 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !304
  %145 = load i32, i32* %arrayidx336, align 4, !dbg !304
  %shr337 = lshr i32 %145, 19, !dbg !304
  %arrayidx338 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !304
  %146 = load i32, i32* %arrayidx338, align 4, !dbg !304
  %shl339 = shl i32 %146, 13, !dbg !304
  %or340 = or i32 %shr337, %shl339, !dbg !304
  %xor341 = xor i32 %or335, %or340, !dbg !304
  %arrayidx342 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !304
  %147 = load i32, i32* %arrayidx342, align 4, !dbg !304
  %shr343 = lshr i32 %147, 10, !dbg !304
  %xor344 = xor i32 %xor341, %shr343, !dbg !304
  %arrayidx345 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !304
  %148 = load i32, i32* %arrayidx345, align 16, !dbg !304
  %add346 = add i32 %xor344, %148, !dbg !304
  %arrayidx347 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !304
  %149 = load i32, i32* %arrayidx347, align 16, !dbg !304
  %shr348 = lshr i32 %149, 7, !dbg !304
  %arrayidx349 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !304
  %150 = load i32, i32* %arrayidx349, align 16, !dbg !304
  %shl350 = shl i32 %150, 25, !dbg !304
  %or351 = or i32 %shr348, %shl350, !dbg !304
  %arrayidx352 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !304
  %151 = load i32, i32* %arrayidx352, align 16, !dbg !304
  %shr353 = lshr i32 %151, 18, !dbg !304
  %arrayidx354 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !304
  %152 = load i32, i32* %arrayidx354, align 16, !dbg !304
  %shl355 = shl i32 %152, 14, !dbg !304
  %or356 = or i32 %shr353, %shl355, !dbg !304
  %xor357 = xor i32 %or351, %or356, !dbg !304
  %arrayidx358 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !304
  %153 = load i32, i32* %arrayidx358, align 16, !dbg !304
  %shr359 = lshr i32 %153, 3, !dbg !304
  %xor360 = xor i32 %xor357, %shr359, !dbg !304
  %add361 = add i32 %add346, %xor360, !dbg !304
  %arrayidx362 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !304
  %154 = load i32, i32* %arrayidx362, align 4, !dbg !304
  %add363 = add i32 %154, %add361, !dbg !304
  store i32 %add363, i32* %arrayidx362, align 4, !dbg !304
  br label %cond.end367, !dbg !304

cond.false364:                                    ; preds = %cond.end263
  %155 = load i32*, i32** %data.addr, align 8, !dbg !306
  %arrayidx365 = getelementptr inbounds i32, i32* %155, i64 3, !dbg !306
  %156 = load i32, i32* %arrayidx365, align 4, !dbg !306
  %arrayidx366 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !306
  store i32 %156, i32* %arrayidx366, align 4, !dbg !306
  br label %cond.end367, !dbg !306

cond.end367:                                      ; preds = %cond.false364, %cond.true330
  %cond368 = phi i32 [ %add363, %cond.true330 ], [ %156, %cond.false364 ], !dbg !308
  %add369 = add i32 %add328, %cond368, !dbg !308
  %arrayidx370 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !308
  %157 = load i32, i32* %arrayidx370, align 16, !dbg !308
  %add371 = add i32 %157, %add369, !dbg !308
  store i32 %add371, i32* %arrayidx370, align 16, !dbg !308
  %arrayidx372 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !308
  %158 = load i32, i32* %arrayidx372, align 16, !dbg !308
  %arrayidx373 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !308
  %159 = load i32, i32* %arrayidx373, align 16, !dbg !308
  %add374 = add i32 %159, %158, !dbg !308
  store i32 %add374, i32* %arrayidx373, align 16, !dbg !308
  %arrayidx375 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %160 = load i32, i32* %arrayidx375, align 4, !dbg !308
  %shr376 = lshr i32 %160, 2, !dbg !308
  %arrayidx377 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %161 = load i32, i32* %arrayidx377, align 4, !dbg !308
  %shl378 = shl i32 %161, 30, !dbg !308
  %or379 = or i32 %shr376, %shl378, !dbg !308
  %arrayidx380 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %162 = load i32, i32* %arrayidx380, align 4, !dbg !308
  %shr381 = lshr i32 %162, 13, !dbg !308
  %arrayidx382 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %163 = load i32, i32* %arrayidx382, align 4, !dbg !308
  %shl383 = shl i32 %163, 19, !dbg !308
  %or384 = or i32 %shr381, %shl383, !dbg !308
  %xor385 = xor i32 %or379, %or384, !dbg !308
  %arrayidx386 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %164 = load i32, i32* %arrayidx386, align 4, !dbg !308
  %shr387 = lshr i32 %164, 22, !dbg !308
  %arrayidx388 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %165 = load i32, i32* %arrayidx388, align 4, !dbg !308
  %shl389 = shl i32 %165, 10, !dbg !308
  %or390 = or i32 %shr387, %shl389, !dbg !308
  %xor391 = xor i32 %xor385, %or390, !dbg !308
  %arrayidx392 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %166 = load i32, i32* %arrayidx392, align 4, !dbg !308
  %arrayidx393 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !308
  %167 = load i32, i32* %arrayidx393, align 8, !dbg !308
  %and394 = and i32 %166, %167, !dbg !308
  %arrayidx395 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !308
  %168 = load i32, i32* %arrayidx395, align 4, !dbg !308
  %arrayidx396 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !308
  %169 = load i32, i32* %arrayidx396, align 4, !dbg !308
  %arrayidx397 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !308
  %170 = load i32, i32* %arrayidx397, align 8, !dbg !308
  %or398 = or i32 %169, %170, !dbg !308
  %and399 = and i32 %168, %or398, !dbg !308
  %or400 = or i32 %and394, %and399, !dbg !308
  %add401 = add i32 %xor391, %or400, !dbg !308
  %arrayidx402 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !308
  %171 = load i32, i32* %arrayidx402, align 16, !dbg !308
  %add403 = add i32 %171, %add401, !dbg !308
  store i32 %add403, i32* %arrayidx402, align 16, !dbg !308
  %arrayidx404 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %172 = load i32, i32* %arrayidx404, align 16, !dbg !310
  %shr405 = lshr i32 %172, 6, !dbg !310
  %arrayidx406 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %173 = load i32, i32* %arrayidx406, align 16, !dbg !310
  %shl407 = shl i32 %173, 26, !dbg !310
  %or408 = or i32 %shr405, %shl407, !dbg !310
  %arrayidx409 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %174 = load i32, i32* %arrayidx409, align 16, !dbg !310
  %shr410 = lshr i32 %174, 11, !dbg !310
  %arrayidx411 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %175 = load i32, i32* %arrayidx411, align 16, !dbg !310
  %shl412 = shl i32 %175, 21, !dbg !310
  %or413 = or i32 %shr410, %shl412, !dbg !310
  %xor414 = xor i32 %or408, %or413, !dbg !310
  %arrayidx415 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %176 = load i32, i32* %arrayidx415, align 16, !dbg !310
  %shr416 = lshr i32 %176, 25, !dbg !310
  %arrayidx417 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %177 = load i32, i32* %arrayidx417, align 16, !dbg !310
  %shl418 = shl i32 %177, 7, !dbg !310
  %or419 = or i32 %shr416, %shl418, !dbg !310
  %xor420 = xor i32 %xor414, %or419, !dbg !310
  %arrayidx421 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !310
  %178 = load i32, i32* %arrayidx421, align 8, !dbg !310
  %arrayidx422 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !310
  %179 = load i32, i32* %arrayidx422, align 16, !dbg !310
  %arrayidx423 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !310
  %180 = load i32, i32* %arrayidx423, align 4, !dbg !310
  %arrayidx424 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !310
  %181 = load i32, i32* %arrayidx424, align 8, !dbg !310
  %xor425 = xor i32 %180, %181, !dbg !310
  %and426 = and i32 %179, %xor425, !dbg !310
  %xor427 = xor i32 %178, %and426, !dbg !310
  %add428 = add i32 %xor420, %xor427, !dbg !310
  %182 = load i32, i32* %j, align 4, !dbg !310
  %add429 = add i32 4, %182, !dbg !310
  %idxprom430 = zext i32 %add429 to i64, !dbg !310
  %arrayidx431 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom430, !dbg !310
  %183 = load i32, i32* %arrayidx431, align 4, !dbg !310
  %add432 = add i32 %add428, %183, !dbg !310
  %184 = load i32, i32* %j, align 4, !dbg !310
  %tobool433 = icmp ne i32 %184, 0, !dbg !310
  br i1 %tobool433, label %cond.true434, label %cond.false468, !dbg !310

cond.true434:                                     ; preds = %cond.end367
  %arrayidx435 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !311
  %185 = load i32, i32* %arrayidx435, align 8, !dbg !311
  %shr436 = lshr i32 %185, 17, !dbg !311
  %arrayidx437 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !311
  %186 = load i32, i32* %arrayidx437, align 8, !dbg !311
  %shl438 = shl i32 %186, 15, !dbg !311
  %or439 = or i32 %shr436, %shl438, !dbg !311
  %arrayidx440 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !311
  %187 = load i32, i32* %arrayidx440, align 8, !dbg !311
  %shr441 = lshr i32 %187, 19, !dbg !311
  %arrayidx442 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !311
  %188 = load i32, i32* %arrayidx442, align 8, !dbg !311
  %shl443 = shl i32 %188, 13, !dbg !311
  %or444 = or i32 %shr441, %shl443, !dbg !311
  %xor445 = xor i32 %or439, %or444, !dbg !311
  %arrayidx446 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !311
  %189 = load i32, i32* %arrayidx446, align 8, !dbg !311
  %shr447 = lshr i32 %189, 10, !dbg !311
  %xor448 = xor i32 %xor445, %shr447, !dbg !311
  %arrayidx449 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !311
  %190 = load i32, i32* %arrayidx449, align 4, !dbg !311
  %add450 = add i32 %xor448, %190, !dbg !311
  %arrayidx451 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !311
  %191 = load i32, i32* %arrayidx451, align 4, !dbg !311
  %shr452 = lshr i32 %191, 7, !dbg !311
  %arrayidx453 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !311
  %192 = load i32, i32* %arrayidx453, align 4, !dbg !311
  %shl454 = shl i32 %192, 25, !dbg !311
  %or455 = or i32 %shr452, %shl454, !dbg !311
  %arrayidx456 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !311
  %193 = load i32, i32* %arrayidx456, align 4, !dbg !311
  %shr457 = lshr i32 %193, 18, !dbg !311
  %arrayidx458 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !311
  %194 = load i32, i32* %arrayidx458, align 4, !dbg !311
  %shl459 = shl i32 %194, 14, !dbg !311
  %or460 = or i32 %shr457, %shl459, !dbg !311
  %xor461 = xor i32 %or455, %or460, !dbg !311
  %arrayidx462 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !311
  %195 = load i32, i32* %arrayidx462, align 4, !dbg !311
  %shr463 = lshr i32 %195, 3, !dbg !311
  %xor464 = xor i32 %xor461, %shr463, !dbg !311
  %add465 = add i32 %add450, %xor464, !dbg !311
  %arrayidx466 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !311
  %196 = load i32, i32* %arrayidx466, align 16, !dbg !311
  %add467 = add i32 %196, %add465, !dbg !311
  store i32 %add467, i32* %arrayidx466, align 16, !dbg !311
  br label %cond.end471, !dbg !311

cond.false468:                                    ; preds = %cond.end367
  %197 = load i32*, i32** %data.addr, align 8, !dbg !312
  %arrayidx469 = getelementptr inbounds i32, i32* %197, i64 4, !dbg !312
  %198 = load i32, i32* %arrayidx469, align 4, !dbg !312
  %arrayidx470 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !312
  store i32 %198, i32* %arrayidx470, align 16, !dbg !312
  br label %cond.end471, !dbg !312

cond.end471:                                      ; preds = %cond.false468, %cond.true434
  %cond472 = phi i32 [ %add467, %cond.true434 ], [ %198, %cond.false468 ], !dbg !313
  %add473 = add i32 %add432, %cond472, !dbg !313
  %arrayidx474 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !313
  %199 = load i32, i32* %arrayidx474, align 4, !dbg !313
  %add475 = add i32 %199, %add473, !dbg !313
  store i32 %add475, i32* %arrayidx474, align 4, !dbg !313
  %arrayidx476 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !313
  %200 = load i32, i32* %arrayidx476, align 4, !dbg !313
  %arrayidx477 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !313
  %201 = load i32, i32* %arrayidx477, align 4, !dbg !313
  %add478 = add i32 %201, %200, !dbg !313
  store i32 %add478, i32* %arrayidx477, align 4, !dbg !313
  %arrayidx479 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %202 = load i32, i32* %arrayidx479, align 16, !dbg !313
  %shr480 = lshr i32 %202, 2, !dbg !313
  %arrayidx481 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %203 = load i32, i32* %arrayidx481, align 16, !dbg !313
  %shl482 = shl i32 %203, 30, !dbg !313
  %or483 = or i32 %shr480, %shl482, !dbg !313
  %arrayidx484 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %204 = load i32, i32* %arrayidx484, align 16, !dbg !313
  %shr485 = lshr i32 %204, 13, !dbg !313
  %arrayidx486 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %205 = load i32, i32* %arrayidx486, align 16, !dbg !313
  %shl487 = shl i32 %205, 19, !dbg !313
  %or488 = or i32 %shr485, %shl487, !dbg !313
  %xor489 = xor i32 %or483, %or488, !dbg !313
  %arrayidx490 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %206 = load i32, i32* %arrayidx490, align 16, !dbg !313
  %shr491 = lshr i32 %206, 22, !dbg !313
  %arrayidx492 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %207 = load i32, i32* %arrayidx492, align 16, !dbg !313
  %shl493 = shl i32 %207, 10, !dbg !313
  %or494 = or i32 %shr491, %shl493, !dbg !313
  %xor495 = xor i32 %xor489, %or494, !dbg !313
  %arrayidx496 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %208 = load i32, i32* %arrayidx496, align 16, !dbg !313
  %arrayidx497 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !313
  %209 = load i32, i32* %arrayidx497, align 4, !dbg !313
  %and498 = and i32 %208, %209, !dbg !313
  %arrayidx499 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !313
  %210 = load i32, i32* %arrayidx499, align 8, !dbg !313
  %arrayidx500 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !313
  %211 = load i32, i32* %arrayidx500, align 16, !dbg !313
  %arrayidx501 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !313
  %212 = load i32, i32* %arrayidx501, align 4, !dbg !313
  %or502 = or i32 %211, %212, !dbg !313
  %and503 = and i32 %210, %or502, !dbg !313
  %or504 = or i32 %and498, %and503, !dbg !313
  %add505 = add i32 %xor495, %or504, !dbg !313
  %arrayidx506 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !313
  %213 = load i32, i32* %arrayidx506, align 4, !dbg !313
  %add507 = add i32 %213, %add505, !dbg !313
  store i32 %add507, i32* %arrayidx506, align 4, !dbg !313
  %arrayidx508 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %214 = load i32, i32* %arrayidx508, align 4, !dbg !314
  %shr509 = lshr i32 %214, 6, !dbg !314
  %arrayidx510 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %215 = load i32, i32* %arrayidx510, align 4, !dbg !314
  %shl511 = shl i32 %215, 26, !dbg !314
  %or512 = or i32 %shr509, %shl511, !dbg !314
  %arrayidx513 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %216 = load i32, i32* %arrayidx513, align 4, !dbg !314
  %shr514 = lshr i32 %216, 11, !dbg !314
  %arrayidx515 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %217 = load i32, i32* %arrayidx515, align 4, !dbg !314
  %shl516 = shl i32 %217, 21, !dbg !314
  %or517 = or i32 %shr514, %shl516, !dbg !314
  %xor518 = xor i32 %or512, %or517, !dbg !314
  %arrayidx519 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %218 = load i32, i32* %arrayidx519, align 4, !dbg !314
  %shr520 = lshr i32 %218, 25, !dbg !314
  %arrayidx521 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %219 = load i32, i32* %arrayidx521, align 4, !dbg !314
  %shl522 = shl i32 %219, 7, !dbg !314
  %or523 = or i32 %shr520, %shl522, !dbg !314
  %xor524 = xor i32 %xor518, %or523, !dbg !314
  %arrayidx525 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !314
  %220 = load i32, i32* %arrayidx525, align 4, !dbg !314
  %arrayidx526 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !314
  %221 = load i32, i32* %arrayidx526, align 4, !dbg !314
  %arrayidx527 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !314
  %222 = load i32, i32* %arrayidx527, align 16, !dbg !314
  %arrayidx528 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !314
  %223 = load i32, i32* %arrayidx528, align 4, !dbg !314
  %xor529 = xor i32 %222, %223, !dbg !314
  %and530 = and i32 %221, %xor529, !dbg !314
  %xor531 = xor i32 %220, %and530, !dbg !314
  %add532 = add i32 %xor524, %xor531, !dbg !314
  %224 = load i32, i32* %j, align 4, !dbg !314
  %add533 = add i32 5, %224, !dbg !314
  %idxprom534 = zext i32 %add533 to i64, !dbg !314
  %arrayidx535 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom534, !dbg !314
  %225 = load i32, i32* %arrayidx535, align 4, !dbg !314
  %add536 = add i32 %add532, %225, !dbg !314
  %226 = load i32, i32* %j, align 4, !dbg !314
  %tobool537 = icmp ne i32 %226, 0, !dbg !314
  br i1 %tobool537, label %cond.true538, label %cond.false572, !dbg !314

cond.true538:                                     ; preds = %cond.end471
  %arrayidx539 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !315
  %227 = load i32, i32* %arrayidx539, align 4, !dbg !315
  %shr540 = lshr i32 %227, 17, !dbg !315
  %arrayidx541 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !315
  %228 = load i32, i32* %arrayidx541, align 4, !dbg !315
  %shl542 = shl i32 %228, 15, !dbg !315
  %or543 = or i32 %shr540, %shl542, !dbg !315
  %arrayidx544 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !315
  %229 = load i32, i32* %arrayidx544, align 4, !dbg !315
  %shr545 = lshr i32 %229, 19, !dbg !315
  %arrayidx546 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !315
  %230 = load i32, i32* %arrayidx546, align 4, !dbg !315
  %shl547 = shl i32 %230, 13, !dbg !315
  %or548 = or i32 %shr545, %shl547, !dbg !315
  %xor549 = xor i32 %or543, %or548, !dbg !315
  %arrayidx550 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !315
  %231 = load i32, i32* %arrayidx550, align 4, !dbg !315
  %shr551 = lshr i32 %231, 10, !dbg !315
  %xor552 = xor i32 %xor549, %shr551, !dbg !315
  %arrayidx553 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !315
  %232 = load i32, i32* %arrayidx553, align 8, !dbg !315
  %add554 = add i32 %xor552, %232, !dbg !315
  %arrayidx555 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !315
  %233 = load i32, i32* %arrayidx555, align 8, !dbg !315
  %shr556 = lshr i32 %233, 7, !dbg !315
  %arrayidx557 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !315
  %234 = load i32, i32* %arrayidx557, align 8, !dbg !315
  %shl558 = shl i32 %234, 25, !dbg !315
  %or559 = or i32 %shr556, %shl558, !dbg !315
  %arrayidx560 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !315
  %235 = load i32, i32* %arrayidx560, align 8, !dbg !315
  %shr561 = lshr i32 %235, 18, !dbg !315
  %arrayidx562 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !315
  %236 = load i32, i32* %arrayidx562, align 8, !dbg !315
  %shl563 = shl i32 %236, 14, !dbg !315
  %or564 = or i32 %shr561, %shl563, !dbg !315
  %xor565 = xor i32 %or559, %or564, !dbg !315
  %arrayidx566 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !315
  %237 = load i32, i32* %arrayidx566, align 8, !dbg !315
  %shr567 = lshr i32 %237, 3, !dbg !315
  %xor568 = xor i32 %xor565, %shr567, !dbg !315
  %add569 = add i32 %add554, %xor568, !dbg !315
  %arrayidx570 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !315
  %238 = load i32, i32* %arrayidx570, align 4, !dbg !315
  %add571 = add i32 %238, %add569, !dbg !315
  store i32 %add571, i32* %arrayidx570, align 4, !dbg !315
  br label %cond.end575, !dbg !315

cond.false572:                                    ; preds = %cond.end471
  %239 = load i32*, i32** %data.addr, align 8, !dbg !316
  %arrayidx573 = getelementptr inbounds i32, i32* %239, i64 5, !dbg !316
  %240 = load i32, i32* %arrayidx573, align 4, !dbg !316
  %arrayidx574 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !316
  store i32 %240, i32* %arrayidx574, align 4, !dbg !316
  br label %cond.end575, !dbg !316

cond.end575:                                      ; preds = %cond.false572, %cond.true538
  %cond576 = phi i32 [ %add571, %cond.true538 ], [ %240, %cond.false572 ], !dbg !317
  %add577 = add i32 %add536, %cond576, !dbg !317
  %arrayidx578 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !317
  %241 = load i32, i32* %arrayidx578, align 8, !dbg !317
  %add579 = add i32 %241, %add577, !dbg !317
  store i32 %add579, i32* %arrayidx578, align 8, !dbg !317
  %arrayidx580 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !317
  %242 = load i32, i32* %arrayidx580, align 8, !dbg !317
  %arrayidx581 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !317
  %243 = load i32, i32* %arrayidx581, align 8, !dbg !317
  %add582 = add i32 %243, %242, !dbg !317
  store i32 %add582, i32* %arrayidx581, align 8, !dbg !317
  %arrayidx583 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %244 = load i32, i32* %arrayidx583, align 4, !dbg !317
  %shr584 = lshr i32 %244, 2, !dbg !317
  %arrayidx585 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %245 = load i32, i32* %arrayidx585, align 4, !dbg !317
  %shl586 = shl i32 %245, 30, !dbg !317
  %or587 = or i32 %shr584, %shl586, !dbg !317
  %arrayidx588 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %246 = load i32, i32* %arrayidx588, align 4, !dbg !317
  %shr589 = lshr i32 %246, 13, !dbg !317
  %arrayidx590 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %247 = load i32, i32* %arrayidx590, align 4, !dbg !317
  %shl591 = shl i32 %247, 19, !dbg !317
  %or592 = or i32 %shr589, %shl591, !dbg !317
  %xor593 = xor i32 %or587, %or592, !dbg !317
  %arrayidx594 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %248 = load i32, i32* %arrayidx594, align 4, !dbg !317
  %shr595 = lshr i32 %248, 22, !dbg !317
  %arrayidx596 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %249 = load i32, i32* %arrayidx596, align 4, !dbg !317
  %shl597 = shl i32 %249, 10, !dbg !317
  %or598 = or i32 %shr595, %shl597, !dbg !317
  %xor599 = xor i32 %xor593, %or598, !dbg !317
  %arrayidx600 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %250 = load i32, i32* %arrayidx600, align 4, !dbg !317
  %arrayidx601 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !317
  %251 = load i32, i32* %arrayidx601, align 16, !dbg !317
  %and602 = and i32 %250, %251, !dbg !317
  %arrayidx603 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !317
  %252 = load i32, i32* %arrayidx603, align 4, !dbg !317
  %arrayidx604 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !317
  %253 = load i32, i32* %arrayidx604, align 4, !dbg !317
  %arrayidx605 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !317
  %254 = load i32, i32* %arrayidx605, align 16, !dbg !317
  %or606 = or i32 %253, %254, !dbg !317
  %and607 = and i32 %252, %or606, !dbg !317
  %or608 = or i32 %and602, %and607, !dbg !317
  %add609 = add i32 %xor599, %or608, !dbg !317
  %arrayidx610 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !317
  %255 = load i32, i32* %arrayidx610, align 8, !dbg !317
  %add611 = add i32 %255, %add609, !dbg !317
  store i32 %add611, i32* %arrayidx610, align 8, !dbg !317
  %arrayidx612 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %256 = load i32, i32* %arrayidx612, align 8, !dbg !318
  %shr613 = lshr i32 %256, 6, !dbg !318
  %arrayidx614 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %257 = load i32, i32* %arrayidx614, align 8, !dbg !318
  %shl615 = shl i32 %257, 26, !dbg !318
  %or616 = or i32 %shr613, %shl615, !dbg !318
  %arrayidx617 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %258 = load i32, i32* %arrayidx617, align 8, !dbg !318
  %shr618 = lshr i32 %258, 11, !dbg !318
  %arrayidx619 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %259 = load i32, i32* %arrayidx619, align 8, !dbg !318
  %shl620 = shl i32 %259, 21, !dbg !318
  %or621 = or i32 %shr618, %shl620, !dbg !318
  %xor622 = xor i32 %or616, %or621, !dbg !318
  %arrayidx623 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %260 = load i32, i32* %arrayidx623, align 8, !dbg !318
  %shr624 = lshr i32 %260, 25, !dbg !318
  %arrayidx625 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %261 = load i32, i32* %arrayidx625, align 8, !dbg !318
  %shl626 = shl i32 %261, 7, !dbg !318
  %or627 = or i32 %shr624, %shl626, !dbg !318
  %xor628 = xor i32 %xor622, %or627, !dbg !318
  %arrayidx629 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !318
  %262 = load i32, i32* %arrayidx629, align 16, !dbg !318
  %arrayidx630 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !318
  %263 = load i32, i32* %arrayidx630, align 8, !dbg !318
  %arrayidx631 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !318
  %264 = load i32, i32* %arrayidx631, align 4, !dbg !318
  %arrayidx632 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !318
  %265 = load i32, i32* %arrayidx632, align 16, !dbg !318
  %xor633 = xor i32 %264, %265, !dbg !318
  %and634 = and i32 %263, %xor633, !dbg !318
  %xor635 = xor i32 %262, %and634, !dbg !318
  %add636 = add i32 %xor628, %xor635, !dbg !318
  %266 = load i32, i32* %j, align 4, !dbg !318
  %add637 = add i32 6, %266, !dbg !318
  %idxprom638 = zext i32 %add637 to i64, !dbg !318
  %arrayidx639 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom638, !dbg !318
  %267 = load i32, i32* %arrayidx639, align 4, !dbg !318
  %add640 = add i32 %add636, %267, !dbg !318
  %268 = load i32, i32* %j, align 4, !dbg !318
  %tobool641 = icmp ne i32 %268, 0, !dbg !318
  br i1 %tobool641, label %cond.true642, label %cond.false676, !dbg !318

cond.true642:                                     ; preds = %cond.end575
  %arrayidx643 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !319
  %269 = load i32, i32* %arrayidx643, align 16, !dbg !319
  %shr644 = lshr i32 %269, 17, !dbg !319
  %arrayidx645 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !319
  %270 = load i32, i32* %arrayidx645, align 16, !dbg !319
  %shl646 = shl i32 %270, 15, !dbg !319
  %or647 = or i32 %shr644, %shl646, !dbg !319
  %arrayidx648 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !319
  %271 = load i32, i32* %arrayidx648, align 16, !dbg !319
  %shr649 = lshr i32 %271, 19, !dbg !319
  %arrayidx650 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !319
  %272 = load i32, i32* %arrayidx650, align 16, !dbg !319
  %shl651 = shl i32 %272, 13, !dbg !319
  %or652 = or i32 %shr649, %shl651, !dbg !319
  %xor653 = xor i32 %or647, %or652, !dbg !319
  %arrayidx654 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !319
  %273 = load i32, i32* %arrayidx654, align 16, !dbg !319
  %shr655 = lshr i32 %273, 10, !dbg !319
  %xor656 = xor i32 %xor653, %shr655, !dbg !319
  %arrayidx657 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !319
  %274 = load i32, i32* %arrayidx657, align 4, !dbg !319
  %add658 = add i32 %xor656, %274, !dbg !319
  %arrayidx659 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !319
  %275 = load i32, i32* %arrayidx659, align 4, !dbg !319
  %shr660 = lshr i32 %275, 7, !dbg !319
  %arrayidx661 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !319
  %276 = load i32, i32* %arrayidx661, align 4, !dbg !319
  %shl662 = shl i32 %276, 25, !dbg !319
  %or663 = or i32 %shr660, %shl662, !dbg !319
  %arrayidx664 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !319
  %277 = load i32, i32* %arrayidx664, align 4, !dbg !319
  %shr665 = lshr i32 %277, 18, !dbg !319
  %arrayidx666 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !319
  %278 = load i32, i32* %arrayidx666, align 4, !dbg !319
  %shl667 = shl i32 %278, 14, !dbg !319
  %or668 = or i32 %shr665, %shl667, !dbg !319
  %xor669 = xor i32 %or663, %or668, !dbg !319
  %arrayidx670 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !319
  %279 = load i32, i32* %arrayidx670, align 4, !dbg !319
  %shr671 = lshr i32 %279, 3, !dbg !319
  %xor672 = xor i32 %xor669, %shr671, !dbg !319
  %add673 = add i32 %add658, %xor672, !dbg !319
  %arrayidx674 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !319
  %280 = load i32, i32* %arrayidx674, align 8, !dbg !319
  %add675 = add i32 %280, %add673, !dbg !319
  store i32 %add675, i32* %arrayidx674, align 8, !dbg !319
  br label %cond.end679, !dbg !319

cond.false676:                                    ; preds = %cond.end575
  %281 = load i32*, i32** %data.addr, align 8, !dbg !320
  %arrayidx677 = getelementptr inbounds i32, i32* %281, i64 6, !dbg !320
  %282 = load i32, i32* %arrayidx677, align 4, !dbg !320
  %arrayidx678 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !320
  store i32 %282, i32* %arrayidx678, align 8, !dbg !320
  br label %cond.end679, !dbg !320

cond.end679:                                      ; preds = %cond.false676, %cond.true642
  %cond680 = phi i32 [ %add675, %cond.true642 ], [ %282, %cond.false676 ], !dbg !321
  %add681 = add i32 %add640, %cond680, !dbg !321
  %arrayidx682 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !321
  %283 = load i32, i32* %arrayidx682, align 4, !dbg !321
  %add683 = add i32 %283, %add681, !dbg !321
  store i32 %add683, i32* %arrayidx682, align 4, !dbg !321
  %arrayidx684 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !321
  %284 = load i32, i32* %arrayidx684, align 4, !dbg !321
  %arrayidx685 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !321
  %285 = load i32, i32* %arrayidx685, align 4, !dbg !321
  %add686 = add i32 %285, %284, !dbg !321
  store i32 %add686, i32* %arrayidx685, align 4, !dbg !321
  %arrayidx687 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %286 = load i32, i32* %arrayidx687, align 8, !dbg !321
  %shr688 = lshr i32 %286, 2, !dbg !321
  %arrayidx689 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %287 = load i32, i32* %arrayidx689, align 8, !dbg !321
  %shl690 = shl i32 %287, 30, !dbg !321
  %or691 = or i32 %shr688, %shl690, !dbg !321
  %arrayidx692 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %288 = load i32, i32* %arrayidx692, align 8, !dbg !321
  %shr693 = lshr i32 %288, 13, !dbg !321
  %arrayidx694 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %289 = load i32, i32* %arrayidx694, align 8, !dbg !321
  %shl695 = shl i32 %289, 19, !dbg !321
  %or696 = or i32 %shr693, %shl695, !dbg !321
  %xor697 = xor i32 %or691, %or696, !dbg !321
  %arrayidx698 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %290 = load i32, i32* %arrayidx698, align 8, !dbg !321
  %shr699 = lshr i32 %290, 22, !dbg !321
  %arrayidx700 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %291 = load i32, i32* %arrayidx700, align 8, !dbg !321
  %shl701 = shl i32 %291, 10, !dbg !321
  %or702 = or i32 %shr699, %shl701, !dbg !321
  %xor703 = xor i32 %xor697, %or702, !dbg !321
  %arrayidx704 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %292 = load i32, i32* %arrayidx704, align 8, !dbg !321
  %arrayidx705 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !321
  %293 = load i32, i32* %arrayidx705, align 4, !dbg !321
  %and706 = and i32 %292, %293, !dbg !321
  %arrayidx707 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !321
  %294 = load i32, i32* %arrayidx707, align 16, !dbg !321
  %arrayidx708 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !321
  %295 = load i32, i32* %arrayidx708, align 8, !dbg !321
  %arrayidx709 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !321
  %296 = load i32, i32* %arrayidx709, align 4, !dbg !321
  %or710 = or i32 %295, %296, !dbg !321
  %and711 = and i32 %294, %or710, !dbg !321
  %or712 = or i32 %and706, %and711, !dbg !321
  %add713 = add i32 %xor703, %or712, !dbg !321
  %arrayidx714 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !321
  %297 = load i32, i32* %arrayidx714, align 4, !dbg !321
  %add715 = add i32 %297, %add713, !dbg !321
  store i32 %add715, i32* %arrayidx714, align 4, !dbg !321
  %arrayidx716 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %298 = load i32, i32* %arrayidx716, align 4, !dbg !322
  %shr717 = lshr i32 %298, 6, !dbg !322
  %arrayidx718 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %299 = load i32, i32* %arrayidx718, align 4, !dbg !322
  %shl719 = shl i32 %299, 26, !dbg !322
  %or720 = or i32 %shr717, %shl719, !dbg !322
  %arrayidx721 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %300 = load i32, i32* %arrayidx721, align 4, !dbg !322
  %shr722 = lshr i32 %300, 11, !dbg !322
  %arrayidx723 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %301 = load i32, i32* %arrayidx723, align 4, !dbg !322
  %shl724 = shl i32 %301, 21, !dbg !322
  %or725 = or i32 %shr722, %shl724, !dbg !322
  %xor726 = xor i32 %or720, %or725, !dbg !322
  %arrayidx727 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %302 = load i32, i32* %arrayidx727, align 4, !dbg !322
  %shr728 = lshr i32 %302, 25, !dbg !322
  %arrayidx729 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %303 = load i32, i32* %arrayidx729, align 4, !dbg !322
  %shl730 = shl i32 %303, 7, !dbg !322
  %or731 = or i32 %shr728, %shl730, !dbg !322
  %xor732 = xor i32 %xor726, %or731, !dbg !322
  %arrayidx733 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !322
  %304 = load i32, i32* %arrayidx733, align 4, !dbg !322
  %arrayidx734 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !322
  %305 = load i32, i32* %arrayidx734, align 4, !dbg !322
  %arrayidx735 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !322
  %306 = load i32, i32* %arrayidx735, align 8, !dbg !322
  %arrayidx736 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !322
  %307 = load i32, i32* %arrayidx736, align 4, !dbg !322
  %xor737 = xor i32 %306, %307, !dbg !322
  %and738 = and i32 %305, %xor737, !dbg !322
  %xor739 = xor i32 %304, %and738, !dbg !322
  %add740 = add i32 %xor732, %xor739, !dbg !322
  %308 = load i32, i32* %j, align 4, !dbg !322
  %add741 = add i32 7, %308, !dbg !322
  %idxprom742 = zext i32 %add741 to i64, !dbg !322
  %arrayidx743 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom742, !dbg !322
  %309 = load i32, i32* %arrayidx743, align 4, !dbg !322
  %add744 = add i32 %add740, %309, !dbg !322
  %310 = load i32, i32* %j, align 4, !dbg !322
  %tobool745 = icmp ne i32 %310, 0, !dbg !322
  br i1 %tobool745, label %cond.true746, label %cond.false780, !dbg !322

cond.true746:                                     ; preds = %cond.end679
  %arrayidx747 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !323
  %311 = load i32, i32* %arrayidx747, align 4, !dbg !323
  %shr748 = lshr i32 %311, 17, !dbg !323
  %arrayidx749 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !323
  %312 = load i32, i32* %arrayidx749, align 4, !dbg !323
  %shl750 = shl i32 %312, 15, !dbg !323
  %or751 = or i32 %shr748, %shl750, !dbg !323
  %arrayidx752 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !323
  %313 = load i32, i32* %arrayidx752, align 4, !dbg !323
  %shr753 = lshr i32 %313, 19, !dbg !323
  %arrayidx754 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !323
  %314 = load i32, i32* %arrayidx754, align 4, !dbg !323
  %shl755 = shl i32 %314, 13, !dbg !323
  %or756 = or i32 %shr753, %shl755, !dbg !323
  %xor757 = xor i32 %or751, %or756, !dbg !323
  %arrayidx758 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !323
  %315 = load i32, i32* %arrayidx758, align 4, !dbg !323
  %shr759 = lshr i32 %315, 10, !dbg !323
  %xor760 = xor i32 %xor757, %shr759, !dbg !323
  %arrayidx761 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !323
  %316 = load i32, i32* %arrayidx761, align 16, !dbg !323
  %add762 = add i32 %xor760, %316, !dbg !323
  %arrayidx763 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !323
  %317 = load i32, i32* %arrayidx763, align 16, !dbg !323
  %shr764 = lshr i32 %317, 7, !dbg !323
  %arrayidx765 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !323
  %318 = load i32, i32* %arrayidx765, align 16, !dbg !323
  %shl766 = shl i32 %318, 25, !dbg !323
  %or767 = or i32 %shr764, %shl766, !dbg !323
  %arrayidx768 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !323
  %319 = load i32, i32* %arrayidx768, align 16, !dbg !323
  %shr769 = lshr i32 %319, 18, !dbg !323
  %arrayidx770 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !323
  %320 = load i32, i32* %arrayidx770, align 16, !dbg !323
  %shl771 = shl i32 %320, 14, !dbg !323
  %or772 = or i32 %shr769, %shl771, !dbg !323
  %xor773 = xor i32 %or767, %or772, !dbg !323
  %arrayidx774 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !323
  %321 = load i32, i32* %arrayidx774, align 16, !dbg !323
  %shr775 = lshr i32 %321, 3, !dbg !323
  %xor776 = xor i32 %xor773, %shr775, !dbg !323
  %add777 = add i32 %add762, %xor776, !dbg !323
  %arrayidx778 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !323
  %322 = load i32, i32* %arrayidx778, align 4, !dbg !323
  %add779 = add i32 %322, %add777, !dbg !323
  store i32 %add779, i32* %arrayidx778, align 4, !dbg !323
  br label %cond.end783, !dbg !323

cond.false780:                                    ; preds = %cond.end679
  %323 = load i32*, i32** %data.addr, align 8, !dbg !324
  %arrayidx781 = getelementptr inbounds i32, i32* %323, i64 7, !dbg !324
  %324 = load i32, i32* %arrayidx781, align 4, !dbg !324
  %arrayidx782 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !324
  store i32 %324, i32* %arrayidx782, align 4, !dbg !324
  br label %cond.end783, !dbg !324

cond.end783:                                      ; preds = %cond.false780, %cond.true746
  %cond784 = phi i32 [ %add779, %cond.true746 ], [ %324, %cond.false780 ], !dbg !325
  %add785 = add i32 %add744, %cond784, !dbg !325
  %arrayidx786 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !325
  %325 = load i32, i32* %arrayidx786, align 16, !dbg !325
  %add787 = add i32 %325, %add785, !dbg !325
  store i32 %add787, i32* %arrayidx786, align 16, !dbg !325
  %arrayidx788 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !325
  %326 = load i32, i32* %arrayidx788, align 16, !dbg !325
  %arrayidx789 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !325
  %327 = load i32, i32* %arrayidx789, align 16, !dbg !325
  %add790 = add i32 %327, %326, !dbg !325
  store i32 %add790, i32* %arrayidx789, align 16, !dbg !325
  %arrayidx791 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %328 = load i32, i32* %arrayidx791, align 4, !dbg !325
  %shr792 = lshr i32 %328, 2, !dbg !325
  %arrayidx793 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %329 = load i32, i32* %arrayidx793, align 4, !dbg !325
  %shl794 = shl i32 %329, 30, !dbg !325
  %or795 = or i32 %shr792, %shl794, !dbg !325
  %arrayidx796 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %330 = load i32, i32* %arrayidx796, align 4, !dbg !325
  %shr797 = lshr i32 %330, 13, !dbg !325
  %arrayidx798 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %331 = load i32, i32* %arrayidx798, align 4, !dbg !325
  %shl799 = shl i32 %331, 19, !dbg !325
  %or800 = or i32 %shr797, %shl799, !dbg !325
  %xor801 = xor i32 %or795, %or800, !dbg !325
  %arrayidx802 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %332 = load i32, i32* %arrayidx802, align 4, !dbg !325
  %shr803 = lshr i32 %332, 22, !dbg !325
  %arrayidx804 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %333 = load i32, i32* %arrayidx804, align 4, !dbg !325
  %shl805 = shl i32 %333, 10, !dbg !325
  %or806 = or i32 %shr803, %shl805, !dbg !325
  %xor807 = xor i32 %xor801, %or806, !dbg !325
  %arrayidx808 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %334 = load i32, i32* %arrayidx808, align 4, !dbg !325
  %arrayidx809 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !325
  %335 = load i32, i32* %arrayidx809, align 8, !dbg !325
  %and810 = and i32 %334, %335, !dbg !325
  %arrayidx811 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !325
  %336 = load i32, i32* %arrayidx811, align 4, !dbg !325
  %arrayidx812 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !325
  %337 = load i32, i32* %arrayidx812, align 4, !dbg !325
  %arrayidx813 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !325
  %338 = load i32, i32* %arrayidx813, align 8, !dbg !325
  %or814 = or i32 %337, %338, !dbg !325
  %and815 = and i32 %336, %or814, !dbg !325
  %or816 = or i32 %and810, %and815, !dbg !325
  %add817 = add i32 %xor807, %or816, !dbg !325
  %arrayidx818 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !325
  %339 = load i32, i32* %arrayidx818, align 16, !dbg !325
  %add819 = add i32 %339, %add817, !dbg !325
  store i32 %add819, i32* %arrayidx818, align 16, !dbg !325
  %arrayidx820 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %340 = load i32, i32* %arrayidx820, align 16, !dbg !326
  %shr821 = lshr i32 %340, 6, !dbg !326
  %arrayidx822 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %341 = load i32, i32* %arrayidx822, align 16, !dbg !326
  %shl823 = shl i32 %341, 26, !dbg !326
  %or824 = or i32 %shr821, %shl823, !dbg !326
  %arrayidx825 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %342 = load i32, i32* %arrayidx825, align 16, !dbg !326
  %shr826 = lshr i32 %342, 11, !dbg !326
  %arrayidx827 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %343 = load i32, i32* %arrayidx827, align 16, !dbg !326
  %shl828 = shl i32 %343, 21, !dbg !326
  %or829 = or i32 %shr826, %shl828, !dbg !326
  %xor830 = xor i32 %or824, %or829, !dbg !326
  %arrayidx831 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %344 = load i32, i32* %arrayidx831, align 16, !dbg !326
  %shr832 = lshr i32 %344, 25, !dbg !326
  %arrayidx833 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %345 = load i32, i32* %arrayidx833, align 16, !dbg !326
  %shl834 = shl i32 %345, 7, !dbg !326
  %or835 = or i32 %shr832, %shl834, !dbg !326
  %xor836 = xor i32 %xor830, %or835, !dbg !326
  %arrayidx837 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !326
  %346 = load i32, i32* %arrayidx837, align 8, !dbg !326
  %arrayidx838 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !326
  %347 = load i32, i32* %arrayidx838, align 16, !dbg !326
  %arrayidx839 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !326
  %348 = load i32, i32* %arrayidx839, align 4, !dbg !326
  %arrayidx840 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !326
  %349 = load i32, i32* %arrayidx840, align 8, !dbg !326
  %xor841 = xor i32 %348, %349, !dbg !326
  %and842 = and i32 %347, %xor841, !dbg !326
  %xor843 = xor i32 %346, %and842, !dbg !326
  %add844 = add i32 %xor836, %xor843, !dbg !326
  %350 = load i32, i32* %j, align 4, !dbg !326
  %add845 = add i32 8, %350, !dbg !326
  %idxprom846 = zext i32 %add845 to i64, !dbg !326
  %arrayidx847 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom846, !dbg !326
  %351 = load i32, i32* %arrayidx847, align 4, !dbg !326
  %add848 = add i32 %add844, %351, !dbg !326
  %352 = load i32, i32* %j, align 4, !dbg !326
  %tobool849 = icmp ne i32 %352, 0, !dbg !326
  br i1 %tobool849, label %cond.true850, label %cond.false884, !dbg !326

cond.true850:                                     ; preds = %cond.end783
  %arrayidx851 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !327
  %353 = load i32, i32* %arrayidx851, align 8, !dbg !327
  %shr852 = lshr i32 %353, 17, !dbg !327
  %arrayidx853 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !327
  %354 = load i32, i32* %arrayidx853, align 8, !dbg !327
  %shl854 = shl i32 %354, 15, !dbg !327
  %or855 = or i32 %shr852, %shl854, !dbg !327
  %arrayidx856 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !327
  %355 = load i32, i32* %arrayidx856, align 8, !dbg !327
  %shr857 = lshr i32 %355, 19, !dbg !327
  %arrayidx858 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !327
  %356 = load i32, i32* %arrayidx858, align 8, !dbg !327
  %shl859 = shl i32 %356, 13, !dbg !327
  %or860 = or i32 %shr857, %shl859, !dbg !327
  %xor861 = xor i32 %or855, %or860, !dbg !327
  %arrayidx862 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !327
  %357 = load i32, i32* %arrayidx862, align 8, !dbg !327
  %shr863 = lshr i32 %357, 10, !dbg !327
  %xor864 = xor i32 %xor861, %shr863, !dbg !327
  %arrayidx865 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 1, !dbg !327
  %358 = load i32, i32* %arrayidx865, align 4, !dbg !327
  %add866 = add i32 %xor864, %358, !dbg !327
  %arrayidx867 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !327
  %359 = load i32, i32* %arrayidx867, align 4, !dbg !327
  %shr868 = lshr i32 %359, 7, !dbg !327
  %arrayidx869 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !327
  %360 = load i32, i32* %arrayidx869, align 4, !dbg !327
  %shl870 = shl i32 %360, 25, !dbg !327
  %or871 = or i32 %shr868, %shl870, !dbg !327
  %arrayidx872 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !327
  %361 = load i32, i32* %arrayidx872, align 4, !dbg !327
  %shr873 = lshr i32 %361, 18, !dbg !327
  %arrayidx874 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !327
  %362 = load i32, i32* %arrayidx874, align 4, !dbg !327
  %shl875 = shl i32 %362, 14, !dbg !327
  %or876 = or i32 %shr873, %shl875, !dbg !327
  %xor877 = xor i32 %or871, %or876, !dbg !327
  %arrayidx878 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !327
  %363 = load i32, i32* %arrayidx878, align 4, !dbg !327
  %shr879 = lshr i32 %363, 3, !dbg !327
  %xor880 = xor i32 %xor877, %shr879, !dbg !327
  %add881 = add i32 %add866, %xor880, !dbg !327
  %arrayidx882 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !327
  %364 = load i32, i32* %arrayidx882, align 16, !dbg !327
  %add883 = add i32 %364, %add881, !dbg !327
  store i32 %add883, i32* %arrayidx882, align 16, !dbg !327
  br label %cond.end887, !dbg !327

cond.false884:                                    ; preds = %cond.end783
  %365 = load i32*, i32** %data.addr, align 8, !dbg !328
  %arrayidx885 = getelementptr inbounds i32, i32* %365, i64 8, !dbg !328
  %366 = load i32, i32* %arrayidx885, align 4, !dbg !328
  %arrayidx886 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !328
  store i32 %366, i32* %arrayidx886, align 16, !dbg !328
  br label %cond.end887, !dbg !328

cond.end887:                                      ; preds = %cond.false884, %cond.true850
  %cond888 = phi i32 [ %add883, %cond.true850 ], [ %366, %cond.false884 ], !dbg !329
  %add889 = add i32 %add848, %cond888, !dbg !329
  %arrayidx890 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !329
  %367 = load i32, i32* %arrayidx890, align 4, !dbg !329
  %add891 = add i32 %367, %add889, !dbg !329
  store i32 %add891, i32* %arrayidx890, align 4, !dbg !329
  %arrayidx892 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !329
  %368 = load i32, i32* %arrayidx892, align 4, !dbg !329
  %arrayidx893 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !329
  %369 = load i32, i32* %arrayidx893, align 4, !dbg !329
  %add894 = add i32 %369, %368, !dbg !329
  store i32 %add894, i32* %arrayidx893, align 4, !dbg !329
  %arrayidx895 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %370 = load i32, i32* %arrayidx895, align 16, !dbg !329
  %shr896 = lshr i32 %370, 2, !dbg !329
  %arrayidx897 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %371 = load i32, i32* %arrayidx897, align 16, !dbg !329
  %shl898 = shl i32 %371, 30, !dbg !329
  %or899 = or i32 %shr896, %shl898, !dbg !329
  %arrayidx900 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %372 = load i32, i32* %arrayidx900, align 16, !dbg !329
  %shr901 = lshr i32 %372, 13, !dbg !329
  %arrayidx902 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %373 = load i32, i32* %arrayidx902, align 16, !dbg !329
  %shl903 = shl i32 %373, 19, !dbg !329
  %or904 = or i32 %shr901, %shl903, !dbg !329
  %xor905 = xor i32 %or899, %or904, !dbg !329
  %arrayidx906 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %374 = load i32, i32* %arrayidx906, align 16, !dbg !329
  %shr907 = lshr i32 %374, 22, !dbg !329
  %arrayidx908 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %375 = load i32, i32* %arrayidx908, align 16, !dbg !329
  %shl909 = shl i32 %375, 10, !dbg !329
  %or910 = or i32 %shr907, %shl909, !dbg !329
  %xor911 = xor i32 %xor905, %or910, !dbg !329
  %arrayidx912 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %376 = load i32, i32* %arrayidx912, align 16, !dbg !329
  %arrayidx913 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !329
  %377 = load i32, i32* %arrayidx913, align 4, !dbg !329
  %and914 = and i32 %376, %377, !dbg !329
  %arrayidx915 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !329
  %378 = load i32, i32* %arrayidx915, align 8, !dbg !329
  %arrayidx916 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !329
  %379 = load i32, i32* %arrayidx916, align 16, !dbg !329
  %arrayidx917 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !329
  %380 = load i32, i32* %arrayidx917, align 4, !dbg !329
  %or918 = or i32 %379, %380, !dbg !329
  %and919 = and i32 %378, %or918, !dbg !329
  %or920 = or i32 %and914, %and919, !dbg !329
  %add921 = add i32 %xor911, %or920, !dbg !329
  %arrayidx922 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !329
  %381 = load i32, i32* %arrayidx922, align 4, !dbg !329
  %add923 = add i32 %381, %add921, !dbg !329
  store i32 %add923, i32* %arrayidx922, align 4, !dbg !329
  %arrayidx924 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %382 = load i32, i32* %arrayidx924, align 4, !dbg !330
  %shr925 = lshr i32 %382, 6, !dbg !330
  %arrayidx926 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %383 = load i32, i32* %arrayidx926, align 4, !dbg !330
  %shl927 = shl i32 %383, 26, !dbg !330
  %or928 = or i32 %shr925, %shl927, !dbg !330
  %arrayidx929 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %384 = load i32, i32* %arrayidx929, align 4, !dbg !330
  %shr930 = lshr i32 %384, 11, !dbg !330
  %arrayidx931 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %385 = load i32, i32* %arrayidx931, align 4, !dbg !330
  %shl932 = shl i32 %385, 21, !dbg !330
  %or933 = or i32 %shr930, %shl932, !dbg !330
  %xor934 = xor i32 %or928, %or933, !dbg !330
  %arrayidx935 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %386 = load i32, i32* %arrayidx935, align 4, !dbg !330
  %shr936 = lshr i32 %386, 25, !dbg !330
  %arrayidx937 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %387 = load i32, i32* %arrayidx937, align 4, !dbg !330
  %shl938 = shl i32 %387, 7, !dbg !330
  %or939 = or i32 %shr936, %shl938, !dbg !330
  %xor940 = xor i32 %xor934, %or939, !dbg !330
  %arrayidx941 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !330
  %388 = load i32, i32* %arrayidx941, align 4, !dbg !330
  %arrayidx942 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !330
  %389 = load i32, i32* %arrayidx942, align 4, !dbg !330
  %arrayidx943 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !330
  %390 = load i32, i32* %arrayidx943, align 16, !dbg !330
  %arrayidx944 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !330
  %391 = load i32, i32* %arrayidx944, align 4, !dbg !330
  %xor945 = xor i32 %390, %391, !dbg !330
  %and946 = and i32 %389, %xor945, !dbg !330
  %xor947 = xor i32 %388, %and946, !dbg !330
  %add948 = add i32 %xor940, %xor947, !dbg !330
  %392 = load i32, i32* %j, align 4, !dbg !330
  %add949 = add i32 9, %392, !dbg !330
  %idxprom950 = zext i32 %add949 to i64, !dbg !330
  %arrayidx951 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom950, !dbg !330
  %393 = load i32, i32* %arrayidx951, align 4, !dbg !330
  %add952 = add i32 %add948, %393, !dbg !330
  %394 = load i32, i32* %j, align 4, !dbg !330
  %tobool953 = icmp ne i32 %394, 0, !dbg !330
  br i1 %tobool953, label %cond.true954, label %cond.false988, !dbg !330

cond.true954:                                     ; preds = %cond.end887
  %arrayidx955 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !331
  %395 = load i32, i32* %arrayidx955, align 4, !dbg !331
  %shr956 = lshr i32 %395, 17, !dbg !331
  %arrayidx957 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !331
  %396 = load i32, i32* %arrayidx957, align 4, !dbg !331
  %shl958 = shl i32 %396, 15, !dbg !331
  %or959 = or i32 %shr956, %shl958, !dbg !331
  %arrayidx960 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !331
  %397 = load i32, i32* %arrayidx960, align 4, !dbg !331
  %shr961 = lshr i32 %397, 19, !dbg !331
  %arrayidx962 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !331
  %398 = load i32, i32* %arrayidx962, align 4, !dbg !331
  %shl963 = shl i32 %398, 13, !dbg !331
  %or964 = or i32 %shr961, %shl963, !dbg !331
  %xor965 = xor i32 %or959, %or964, !dbg !331
  %arrayidx966 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !331
  %399 = load i32, i32* %arrayidx966, align 4, !dbg !331
  %shr967 = lshr i32 %399, 10, !dbg !331
  %xor968 = xor i32 %xor965, %shr967, !dbg !331
  %arrayidx969 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 2, !dbg !331
  %400 = load i32, i32* %arrayidx969, align 8, !dbg !331
  %add970 = add i32 %xor968, %400, !dbg !331
  %arrayidx971 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !331
  %401 = load i32, i32* %arrayidx971, align 8, !dbg !331
  %shr972 = lshr i32 %401, 7, !dbg !331
  %arrayidx973 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !331
  %402 = load i32, i32* %arrayidx973, align 8, !dbg !331
  %shl974 = shl i32 %402, 25, !dbg !331
  %or975 = or i32 %shr972, %shl974, !dbg !331
  %arrayidx976 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !331
  %403 = load i32, i32* %arrayidx976, align 8, !dbg !331
  %shr977 = lshr i32 %403, 18, !dbg !331
  %arrayidx978 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !331
  %404 = load i32, i32* %arrayidx978, align 8, !dbg !331
  %shl979 = shl i32 %404, 14, !dbg !331
  %or980 = or i32 %shr977, %shl979, !dbg !331
  %xor981 = xor i32 %or975, %or980, !dbg !331
  %arrayidx982 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !331
  %405 = load i32, i32* %arrayidx982, align 8, !dbg !331
  %shr983 = lshr i32 %405, 3, !dbg !331
  %xor984 = xor i32 %xor981, %shr983, !dbg !331
  %add985 = add i32 %add970, %xor984, !dbg !331
  %arrayidx986 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !331
  %406 = load i32, i32* %arrayidx986, align 4, !dbg !331
  %add987 = add i32 %406, %add985, !dbg !331
  store i32 %add987, i32* %arrayidx986, align 4, !dbg !331
  br label %cond.end991, !dbg !331

cond.false988:                                    ; preds = %cond.end887
  %407 = load i32*, i32** %data.addr, align 8, !dbg !332
  %arrayidx989 = getelementptr inbounds i32, i32* %407, i64 9, !dbg !332
  %408 = load i32, i32* %arrayidx989, align 4, !dbg !332
  %arrayidx990 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !332
  store i32 %408, i32* %arrayidx990, align 4, !dbg !332
  br label %cond.end991, !dbg !332

cond.end991:                                      ; preds = %cond.false988, %cond.true954
  %cond992 = phi i32 [ %add987, %cond.true954 ], [ %408, %cond.false988 ], !dbg !333
  %add993 = add i32 %add952, %cond992, !dbg !333
  %arrayidx994 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !333
  %409 = load i32, i32* %arrayidx994, align 8, !dbg !333
  %add995 = add i32 %409, %add993, !dbg !333
  store i32 %add995, i32* %arrayidx994, align 8, !dbg !333
  %arrayidx996 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !333
  %410 = load i32, i32* %arrayidx996, align 8, !dbg !333
  %arrayidx997 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !333
  %411 = load i32, i32* %arrayidx997, align 8, !dbg !333
  %add998 = add i32 %411, %410, !dbg !333
  store i32 %add998, i32* %arrayidx997, align 8, !dbg !333
  %arrayidx999 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %412 = load i32, i32* %arrayidx999, align 4, !dbg !333
  %shr1000 = lshr i32 %412, 2, !dbg !333
  %arrayidx1001 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %413 = load i32, i32* %arrayidx1001, align 4, !dbg !333
  %shl1002 = shl i32 %413, 30, !dbg !333
  %or1003 = or i32 %shr1000, %shl1002, !dbg !333
  %arrayidx1004 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %414 = load i32, i32* %arrayidx1004, align 4, !dbg !333
  %shr1005 = lshr i32 %414, 13, !dbg !333
  %arrayidx1006 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %415 = load i32, i32* %arrayidx1006, align 4, !dbg !333
  %shl1007 = shl i32 %415, 19, !dbg !333
  %or1008 = or i32 %shr1005, %shl1007, !dbg !333
  %xor1009 = xor i32 %or1003, %or1008, !dbg !333
  %arrayidx1010 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %416 = load i32, i32* %arrayidx1010, align 4, !dbg !333
  %shr1011 = lshr i32 %416, 22, !dbg !333
  %arrayidx1012 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %417 = load i32, i32* %arrayidx1012, align 4, !dbg !333
  %shl1013 = shl i32 %417, 10, !dbg !333
  %or1014 = or i32 %shr1011, %shl1013, !dbg !333
  %xor1015 = xor i32 %xor1009, %or1014, !dbg !333
  %arrayidx1016 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %418 = load i32, i32* %arrayidx1016, align 4, !dbg !333
  %arrayidx1017 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !333
  %419 = load i32, i32* %arrayidx1017, align 16, !dbg !333
  %and1018 = and i32 %418, %419, !dbg !333
  %arrayidx1019 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !333
  %420 = load i32, i32* %arrayidx1019, align 4, !dbg !333
  %arrayidx1020 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !333
  %421 = load i32, i32* %arrayidx1020, align 4, !dbg !333
  %arrayidx1021 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !333
  %422 = load i32, i32* %arrayidx1021, align 16, !dbg !333
  %or1022 = or i32 %421, %422, !dbg !333
  %and1023 = and i32 %420, %or1022, !dbg !333
  %or1024 = or i32 %and1018, %and1023, !dbg !333
  %add1025 = add i32 %xor1015, %or1024, !dbg !333
  %arrayidx1026 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !333
  %423 = load i32, i32* %arrayidx1026, align 8, !dbg !333
  %add1027 = add i32 %423, %add1025, !dbg !333
  store i32 %add1027, i32* %arrayidx1026, align 8, !dbg !333
  %arrayidx1028 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %424 = load i32, i32* %arrayidx1028, align 8, !dbg !334
  %shr1029 = lshr i32 %424, 6, !dbg !334
  %arrayidx1030 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %425 = load i32, i32* %arrayidx1030, align 8, !dbg !334
  %shl1031 = shl i32 %425, 26, !dbg !334
  %or1032 = or i32 %shr1029, %shl1031, !dbg !334
  %arrayidx1033 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %426 = load i32, i32* %arrayidx1033, align 8, !dbg !334
  %shr1034 = lshr i32 %426, 11, !dbg !334
  %arrayidx1035 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %427 = load i32, i32* %arrayidx1035, align 8, !dbg !334
  %shl1036 = shl i32 %427, 21, !dbg !334
  %or1037 = or i32 %shr1034, %shl1036, !dbg !334
  %xor1038 = xor i32 %or1032, %or1037, !dbg !334
  %arrayidx1039 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %428 = load i32, i32* %arrayidx1039, align 8, !dbg !334
  %shr1040 = lshr i32 %428, 25, !dbg !334
  %arrayidx1041 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %429 = load i32, i32* %arrayidx1041, align 8, !dbg !334
  %shl1042 = shl i32 %429, 7, !dbg !334
  %or1043 = or i32 %shr1040, %shl1042, !dbg !334
  %xor1044 = xor i32 %xor1038, %or1043, !dbg !334
  %arrayidx1045 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !334
  %430 = load i32, i32* %arrayidx1045, align 16, !dbg !334
  %arrayidx1046 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !334
  %431 = load i32, i32* %arrayidx1046, align 8, !dbg !334
  %arrayidx1047 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !334
  %432 = load i32, i32* %arrayidx1047, align 4, !dbg !334
  %arrayidx1048 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !334
  %433 = load i32, i32* %arrayidx1048, align 16, !dbg !334
  %xor1049 = xor i32 %432, %433, !dbg !334
  %and1050 = and i32 %431, %xor1049, !dbg !334
  %xor1051 = xor i32 %430, %and1050, !dbg !334
  %add1052 = add i32 %xor1044, %xor1051, !dbg !334
  %434 = load i32, i32* %j, align 4, !dbg !334
  %add1053 = add i32 10, %434, !dbg !334
  %idxprom1054 = zext i32 %add1053 to i64, !dbg !334
  %arrayidx1055 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom1054, !dbg !334
  %435 = load i32, i32* %arrayidx1055, align 4, !dbg !334
  %add1056 = add i32 %add1052, %435, !dbg !334
  %436 = load i32, i32* %j, align 4, !dbg !334
  %tobool1057 = icmp ne i32 %436, 0, !dbg !334
  br i1 %tobool1057, label %cond.true1058, label %cond.false1092, !dbg !334

cond.true1058:                                    ; preds = %cond.end991
  %arrayidx1059 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !335
  %437 = load i32, i32* %arrayidx1059, align 16, !dbg !335
  %shr1060 = lshr i32 %437, 17, !dbg !335
  %arrayidx1061 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !335
  %438 = load i32, i32* %arrayidx1061, align 16, !dbg !335
  %shl1062 = shl i32 %438, 15, !dbg !335
  %or1063 = or i32 %shr1060, %shl1062, !dbg !335
  %arrayidx1064 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !335
  %439 = load i32, i32* %arrayidx1064, align 16, !dbg !335
  %shr1065 = lshr i32 %439, 19, !dbg !335
  %arrayidx1066 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !335
  %440 = load i32, i32* %arrayidx1066, align 16, !dbg !335
  %shl1067 = shl i32 %440, 13, !dbg !335
  %or1068 = or i32 %shr1065, %shl1067, !dbg !335
  %xor1069 = xor i32 %or1063, %or1068, !dbg !335
  %arrayidx1070 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !335
  %441 = load i32, i32* %arrayidx1070, align 16, !dbg !335
  %shr1071 = lshr i32 %441, 10, !dbg !335
  %xor1072 = xor i32 %xor1069, %shr1071, !dbg !335
  %arrayidx1073 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 3, !dbg !335
  %442 = load i32, i32* %arrayidx1073, align 4, !dbg !335
  %add1074 = add i32 %xor1072, %442, !dbg !335
  %arrayidx1075 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !335
  %443 = load i32, i32* %arrayidx1075, align 4, !dbg !335
  %shr1076 = lshr i32 %443, 7, !dbg !335
  %arrayidx1077 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !335
  %444 = load i32, i32* %arrayidx1077, align 4, !dbg !335
  %shl1078 = shl i32 %444, 25, !dbg !335
  %or1079 = or i32 %shr1076, %shl1078, !dbg !335
  %arrayidx1080 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !335
  %445 = load i32, i32* %arrayidx1080, align 4, !dbg !335
  %shr1081 = lshr i32 %445, 18, !dbg !335
  %arrayidx1082 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !335
  %446 = load i32, i32* %arrayidx1082, align 4, !dbg !335
  %shl1083 = shl i32 %446, 14, !dbg !335
  %or1084 = or i32 %shr1081, %shl1083, !dbg !335
  %xor1085 = xor i32 %or1079, %or1084, !dbg !335
  %arrayidx1086 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !335
  %447 = load i32, i32* %arrayidx1086, align 4, !dbg !335
  %shr1087 = lshr i32 %447, 3, !dbg !335
  %xor1088 = xor i32 %xor1085, %shr1087, !dbg !335
  %add1089 = add i32 %add1074, %xor1088, !dbg !335
  %arrayidx1090 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !335
  %448 = load i32, i32* %arrayidx1090, align 8, !dbg !335
  %add1091 = add i32 %448, %add1089, !dbg !335
  store i32 %add1091, i32* %arrayidx1090, align 8, !dbg !335
  br label %cond.end1095, !dbg !335

cond.false1092:                                   ; preds = %cond.end991
  %449 = load i32*, i32** %data.addr, align 8, !dbg !336
  %arrayidx1093 = getelementptr inbounds i32, i32* %449, i64 10, !dbg !336
  %450 = load i32, i32* %arrayidx1093, align 4, !dbg !336
  %arrayidx1094 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !336
  store i32 %450, i32* %arrayidx1094, align 8, !dbg !336
  br label %cond.end1095, !dbg !336

cond.end1095:                                     ; preds = %cond.false1092, %cond.true1058
  %cond1096 = phi i32 [ %add1091, %cond.true1058 ], [ %450, %cond.false1092 ], !dbg !337
  %add1097 = add i32 %add1056, %cond1096, !dbg !337
  %arrayidx1098 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !337
  %451 = load i32, i32* %arrayidx1098, align 4, !dbg !337
  %add1099 = add i32 %451, %add1097, !dbg !337
  store i32 %add1099, i32* %arrayidx1098, align 4, !dbg !337
  %arrayidx1100 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !337
  %452 = load i32, i32* %arrayidx1100, align 4, !dbg !337
  %arrayidx1101 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !337
  %453 = load i32, i32* %arrayidx1101, align 4, !dbg !337
  %add1102 = add i32 %453, %452, !dbg !337
  store i32 %add1102, i32* %arrayidx1101, align 4, !dbg !337
  %arrayidx1103 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %454 = load i32, i32* %arrayidx1103, align 8, !dbg !337
  %shr1104 = lshr i32 %454, 2, !dbg !337
  %arrayidx1105 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %455 = load i32, i32* %arrayidx1105, align 8, !dbg !337
  %shl1106 = shl i32 %455, 30, !dbg !337
  %or1107 = or i32 %shr1104, %shl1106, !dbg !337
  %arrayidx1108 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %456 = load i32, i32* %arrayidx1108, align 8, !dbg !337
  %shr1109 = lshr i32 %456, 13, !dbg !337
  %arrayidx1110 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %457 = load i32, i32* %arrayidx1110, align 8, !dbg !337
  %shl1111 = shl i32 %457, 19, !dbg !337
  %or1112 = or i32 %shr1109, %shl1111, !dbg !337
  %xor1113 = xor i32 %or1107, %or1112, !dbg !337
  %arrayidx1114 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %458 = load i32, i32* %arrayidx1114, align 8, !dbg !337
  %shr1115 = lshr i32 %458, 22, !dbg !337
  %arrayidx1116 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %459 = load i32, i32* %arrayidx1116, align 8, !dbg !337
  %shl1117 = shl i32 %459, 10, !dbg !337
  %or1118 = or i32 %shr1115, %shl1117, !dbg !337
  %xor1119 = xor i32 %xor1113, %or1118, !dbg !337
  %arrayidx1120 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %460 = load i32, i32* %arrayidx1120, align 8, !dbg !337
  %arrayidx1121 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !337
  %461 = load i32, i32* %arrayidx1121, align 4, !dbg !337
  %and1122 = and i32 %460, %461, !dbg !337
  %arrayidx1123 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !337
  %462 = load i32, i32* %arrayidx1123, align 16, !dbg !337
  %arrayidx1124 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !337
  %463 = load i32, i32* %arrayidx1124, align 8, !dbg !337
  %arrayidx1125 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !337
  %464 = load i32, i32* %arrayidx1125, align 4, !dbg !337
  %or1126 = or i32 %463, %464, !dbg !337
  %and1127 = and i32 %462, %or1126, !dbg !337
  %or1128 = or i32 %and1122, %and1127, !dbg !337
  %add1129 = add i32 %xor1119, %or1128, !dbg !337
  %arrayidx1130 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !337
  %465 = load i32, i32* %arrayidx1130, align 4, !dbg !337
  %add1131 = add i32 %465, %add1129, !dbg !337
  store i32 %add1131, i32* %arrayidx1130, align 4, !dbg !337
  %arrayidx1132 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %466 = load i32, i32* %arrayidx1132, align 4, !dbg !338
  %shr1133 = lshr i32 %466, 6, !dbg !338
  %arrayidx1134 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %467 = load i32, i32* %arrayidx1134, align 4, !dbg !338
  %shl1135 = shl i32 %467, 26, !dbg !338
  %or1136 = or i32 %shr1133, %shl1135, !dbg !338
  %arrayidx1137 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %468 = load i32, i32* %arrayidx1137, align 4, !dbg !338
  %shr1138 = lshr i32 %468, 11, !dbg !338
  %arrayidx1139 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %469 = load i32, i32* %arrayidx1139, align 4, !dbg !338
  %shl1140 = shl i32 %469, 21, !dbg !338
  %or1141 = or i32 %shr1138, %shl1140, !dbg !338
  %xor1142 = xor i32 %or1136, %or1141, !dbg !338
  %arrayidx1143 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %470 = load i32, i32* %arrayidx1143, align 4, !dbg !338
  %shr1144 = lshr i32 %470, 25, !dbg !338
  %arrayidx1145 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %471 = load i32, i32* %arrayidx1145, align 4, !dbg !338
  %shl1146 = shl i32 %471, 7, !dbg !338
  %or1147 = or i32 %shr1144, %shl1146, !dbg !338
  %xor1148 = xor i32 %xor1142, %or1147, !dbg !338
  %arrayidx1149 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !338
  %472 = load i32, i32* %arrayidx1149, align 4, !dbg !338
  %arrayidx1150 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !338
  %473 = load i32, i32* %arrayidx1150, align 4, !dbg !338
  %arrayidx1151 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !338
  %474 = load i32, i32* %arrayidx1151, align 8, !dbg !338
  %arrayidx1152 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !338
  %475 = load i32, i32* %arrayidx1152, align 4, !dbg !338
  %xor1153 = xor i32 %474, %475, !dbg !338
  %and1154 = and i32 %473, %xor1153, !dbg !338
  %xor1155 = xor i32 %472, %and1154, !dbg !338
  %add1156 = add i32 %xor1148, %xor1155, !dbg !338
  %476 = load i32, i32* %j, align 4, !dbg !338
  %add1157 = add i32 11, %476, !dbg !338
  %idxprom1158 = zext i32 %add1157 to i64, !dbg !338
  %arrayidx1159 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom1158, !dbg !338
  %477 = load i32, i32* %arrayidx1159, align 4, !dbg !338
  %add1160 = add i32 %add1156, %477, !dbg !338
  %478 = load i32, i32* %j, align 4, !dbg !338
  %tobool1161 = icmp ne i32 %478, 0, !dbg !338
  br i1 %tobool1161, label %cond.true1162, label %cond.false1196, !dbg !338

cond.true1162:                                    ; preds = %cond.end1095
  %arrayidx1163 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !339
  %479 = load i32, i32* %arrayidx1163, align 4, !dbg !339
  %shr1164 = lshr i32 %479, 17, !dbg !339
  %arrayidx1165 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !339
  %480 = load i32, i32* %arrayidx1165, align 4, !dbg !339
  %shl1166 = shl i32 %480, 15, !dbg !339
  %or1167 = or i32 %shr1164, %shl1166, !dbg !339
  %arrayidx1168 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !339
  %481 = load i32, i32* %arrayidx1168, align 4, !dbg !339
  %shr1169 = lshr i32 %481, 19, !dbg !339
  %arrayidx1170 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !339
  %482 = load i32, i32* %arrayidx1170, align 4, !dbg !339
  %shl1171 = shl i32 %482, 13, !dbg !339
  %or1172 = or i32 %shr1169, %shl1171, !dbg !339
  %xor1173 = xor i32 %or1167, %or1172, !dbg !339
  %arrayidx1174 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 9, !dbg !339
  %483 = load i32, i32* %arrayidx1174, align 4, !dbg !339
  %shr1175 = lshr i32 %483, 10, !dbg !339
  %xor1176 = xor i32 %xor1173, %shr1175, !dbg !339
  %arrayidx1177 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 4, !dbg !339
  %484 = load i32, i32* %arrayidx1177, align 16, !dbg !339
  %add1178 = add i32 %xor1176, %484, !dbg !339
  %arrayidx1179 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !339
  %485 = load i32, i32* %arrayidx1179, align 16, !dbg !339
  %shr1180 = lshr i32 %485, 7, !dbg !339
  %arrayidx1181 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !339
  %486 = load i32, i32* %arrayidx1181, align 16, !dbg !339
  %shl1182 = shl i32 %486, 25, !dbg !339
  %or1183 = or i32 %shr1180, %shl1182, !dbg !339
  %arrayidx1184 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !339
  %487 = load i32, i32* %arrayidx1184, align 16, !dbg !339
  %shr1185 = lshr i32 %487, 18, !dbg !339
  %arrayidx1186 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !339
  %488 = load i32, i32* %arrayidx1186, align 16, !dbg !339
  %shl1187 = shl i32 %488, 14, !dbg !339
  %or1188 = or i32 %shr1185, %shl1187, !dbg !339
  %xor1189 = xor i32 %or1183, %or1188, !dbg !339
  %arrayidx1190 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !339
  %489 = load i32, i32* %arrayidx1190, align 16, !dbg !339
  %shr1191 = lshr i32 %489, 3, !dbg !339
  %xor1192 = xor i32 %xor1189, %shr1191, !dbg !339
  %add1193 = add i32 %add1178, %xor1192, !dbg !339
  %arrayidx1194 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !339
  %490 = load i32, i32* %arrayidx1194, align 4, !dbg !339
  %add1195 = add i32 %490, %add1193, !dbg !339
  store i32 %add1195, i32* %arrayidx1194, align 4, !dbg !339
  br label %cond.end1199, !dbg !339

cond.false1196:                                   ; preds = %cond.end1095
  %491 = load i32*, i32** %data.addr, align 8, !dbg !340
  %arrayidx1197 = getelementptr inbounds i32, i32* %491, i64 11, !dbg !340
  %492 = load i32, i32* %arrayidx1197, align 4, !dbg !340
  %arrayidx1198 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !340
  store i32 %492, i32* %arrayidx1198, align 4, !dbg !340
  br label %cond.end1199, !dbg !340

cond.end1199:                                     ; preds = %cond.false1196, %cond.true1162
  %cond1200 = phi i32 [ %add1195, %cond.true1162 ], [ %492, %cond.false1196 ], !dbg !341
  %add1201 = add i32 %add1160, %cond1200, !dbg !341
  %arrayidx1202 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !341
  %493 = load i32, i32* %arrayidx1202, align 16, !dbg !341
  %add1203 = add i32 %493, %add1201, !dbg !341
  store i32 %add1203, i32* %arrayidx1202, align 16, !dbg !341
  %arrayidx1204 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !341
  %494 = load i32, i32* %arrayidx1204, align 16, !dbg !341
  %arrayidx1205 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !341
  %495 = load i32, i32* %arrayidx1205, align 16, !dbg !341
  %add1206 = add i32 %495, %494, !dbg !341
  store i32 %add1206, i32* %arrayidx1205, align 16, !dbg !341
  %arrayidx1207 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %496 = load i32, i32* %arrayidx1207, align 4, !dbg !341
  %shr1208 = lshr i32 %496, 2, !dbg !341
  %arrayidx1209 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %497 = load i32, i32* %arrayidx1209, align 4, !dbg !341
  %shl1210 = shl i32 %497, 30, !dbg !341
  %or1211 = or i32 %shr1208, %shl1210, !dbg !341
  %arrayidx1212 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %498 = load i32, i32* %arrayidx1212, align 4, !dbg !341
  %shr1213 = lshr i32 %498, 13, !dbg !341
  %arrayidx1214 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %499 = load i32, i32* %arrayidx1214, align 4, !dbg !341
  %shl1215 = shl i32 %499, 19, !dbg !341
  %or1216 = or i32 %shr1213, %shl1215, !dbg !341
  %xor1217 = xor i32 %or1211, %or1216, !dbg !341
  %arrayidx1218 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %500 = load i32, i32* %arrayidx1218, align 4, !dbg !341
  %shr1219 = lshr i32 %500, 22, !dbg !341
  %arrayidx1220 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %501 = load i32, i32* %arrayidx1220, align 4, !dbg !341
  %shl1221 = shl i32 %501, 10, !dbg !341
  %or1222 = or i32 %shr1219, %shl1221, !dbg !341
  %xor1223 = xor i32 %xor1217, %or1222, !dbg !341
  %arrayidx1224 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %502 = load i32, i32* %arrayidx1224, align 4, !dbg !341
  %arrayidx1225 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !341
  %503 = load i32, i32* %arrayidx1225, align 8, !dbg !341
  %and1226 = and i32 %502, %503, !dbg !341
  %arrayidx1227 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !341
  %504 = load i32, i32* %arrayidx1227, align 4, !dbg !341
  %arrayidx1228 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !341
  %505 = load i32, i32* %arrayidx1228, align 4, !dbg !341
  %arrayidx1229 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !341
  %506 = load i32, i32* %arrayidx1229, align 8, !dbg !341
  %or1230 = or i32 %505, %506, !dbg !341
  %and1231 = and i32 %504, %or1230, !dbg !341
  %or1232 = or i32 %and1226, %and1231, !dbg !341
  %add1233 = add i32 %xor1223, %or1232, !dbg !341
  %arrayidx1234 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !341
  %507 = load i32, i32* %arrayidx1234, align 16, !dbg !341
  %add1235 = add i32 %507, %add1233, !dbg !341
  store i32 %add1235, i32* %arrayidx1234, align 16, !dbg !341
  %arrayidx1236 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %508 = load i32, i32* %arrayidx1236, align 16, !dbg !342
  %shr1237 = lshr i32 %508, 6, !dbg !342
  %arrayidx1238 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %509 = load i32, i32* %arrayidx1238, align 16, !dbg !342
  %shl1239 = shl i32 %509, 26, !dbg !342
  %or1240 = or i32 %shr1237, %shl1239, !dbg !342
  %arrayidx1241 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %510 = load i32, i32* %arrayidx1241, align 16, !dbg !342
  %shr1242 = lshr i32 %510, 11, !dbg !342
  %arrayidx1243 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %511 = load i32, i32* %arrayidx1243, align 16, !dbg !342
  %shl1244 = shl i32 %511, 21, !dbg !342
  %or1245 = or i32 %shr1242, %shl1244, !dbg !342
  %xor1246 = xor i32 %or1240, %or1245, !dbg !342
  %arrayidx1247 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %512 = load i32, i32* %arrayidx1247, align 16, !dbg !342
  %shr1248 = lshr i32 %512, 25, !dbg !342
  %arrayidx1249 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %513 = load i32, i32* %arrayidx1249, align 16, !dbg !342
  %shl1250 = shl i32 %513, 7, !dbg !342
  %or1251 = or i32 %shr1248, %shl1250, !dbg !342
  %xor1252 = xor i32 %xor1246, %or1251, !dbg !342
  %arrayidx1253 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !342
  %514 = load i32, i32* %arrayidx1253, align 8, !dbg !342
  %arrayidx1254 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !342
  %515 = load i32, i32* %arrayidx1254, align 16, !dbg !342
  %arrayidx1255 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !342
  %516 = load i32, i32* %arrayidx1255, align 4, !dbg !342
  %arrayidx1256 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !342
  %517 = load i32, i32* %arrayidx1256, align 8, !dbg !342
  %xor1257 = xor i32 %516, %517, !dbg !342
  %and1258 = and i32 %515, %xor1257, !dbg !342
  %xor1259 = xor i32 %514, %and1258, !dbg !342
  %add1260 = add i32 %xor1252, %xor1259, !dbg !342
  %518 = load i32, i32* %j, align 4, !dbg !342
  %add1261 = add i32 12, %518, !dbg !342
  %idxprom1262 = zext i32 %add1261 to i64, !dbg !342
  %arrayidx1263 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom1262, !dbg !342
  %519 = load i32, i32* %arrayidx1263, align 4, !dbg !342
  %add1264 = add i32 %add1260, %519, !dbg !342
  %520 = load i32, i32* %j, align 4, !dbg !342
  %tobool1265 = icmp ne i32 %520, 0, !dbg !342
  br i1 %tobool1265, label %cond.true1266, label %cond.false1300, !dbg !342

cond.true1266:                                    ; preds = %cond.end1199
  %arrayidx1267 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !343
  %521 = load i32, i32* %arrayidx1267, align 8, !dbg !343
  %shr1268 = lshr i32 %521, 17, !dbg !343
  %arrayidx1269 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !343
  %522 = load i32, i32* %arrayidx1269, align 8, !dbg !343
  %shl1270 = shl i32 %522, 15, !dbg !343
  %or1271 = or i32 %shr1268, %shl1270, !dbg !343
  %arrayidx1272 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !343
  %523 = load i32, i32* %arrayidx1272, align 8, !dbg !343
  %shr1273 = lshr i32 %523, 19, !dbg !343
  %arrayidx1274 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !343
  %524 = load i32, i32* %arrayidx1274, align 8, !dbg !343
  %shl1275 = shl i32 %524, 13, !dbg !343
  %or1276 = or i32 %shr1273, %shl1275, !dbg !343
  %xor1277 = xor i32 %or1271, %or1276, !dbg !343
  %arrayidx1278 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 10, !dbg !343
  %525 = load i32, i32* %arrayidx1278, align 8, !dbg !343
  %shr1279 = lshr i32 %525, 10, !dbg !343
  %xor1280 = xor i32 %xor1277, %shr1279, !dbg !343
  %arrayidx1281 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 5, !dbg !343
  %526 = load i32, i32* %arrayidx1281, align 4, !dbg !343
  %add1282 = add i32 %xor1280, %526, !dbg !343
  %arrayidx1283 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !343
  %527 = load i32, i32* %arrayidx1283, align 4, !dbg !343
  %shr1284 = lshr i32 %527, 7, !dbg !343
  %arrayidx1285 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !343
  %528 = load i32, i32* %arrayidx1285, align 4, !dbg !343
  %shl1286 = shl i32 %528, 25, !dbg !343
  %or1287 = or i32 %shr1284, %shl1286, !dbg !343
  %arrayidx1288 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !343
  %529 = load i32, i32* %arrayidx1288, align 4, !dbg !343
  %shr1289 = lshr i32 %529, 18, !dbg !343
  %arrayidx1290 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !343
  %530 = load i32, i32* %arrayidx1290, align 4, !dbg !343
  %shl1291 = shl i32 %530, 14, !dbg !343
  %or1292 = or i32 %shr1289, %shl1291, !dbg !343
  %xor1293 = xor i32 %or1287, %or1292, !dbg !343
  %arrayidx1294 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !343
  %531 = load i32, i32* %arrayidx1294, align 4, !dbg !343
  %shr1295 = lshr i32 %531, 3, !dbg !343
  %xor1296 = xor i32 %xor1293, %shr1295, !dbg !343
  %add1297 = add i32 %add1282, %xor1296, !dbg !343
  %arrayidx1298 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !343
  %532 = load i32, i32* %arrayidx1298, align 16, !dbg !343
  %add1299 = add i32 %532, %add1297, !dbg !343
  store i32 %add1299, i32* %arrayidx1298, align 16, !dbg !343
  br label %cond.end1303, !dbg !343

cond.false1300:                                   ; preds = %cond.end1199
  %533 = load i32*, i32** %data.addr, align 8, !dbg !344
  %arrayidx1301 = getelementptr inbounds i32, i32* %533, i64 12, !dbg !344
  %534 = load i32, i32* %arrayidx1301, align 4, !dbg !344
  %arrayidx1302 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !344
  store i32 %534, i32* %arrayidx1302, align 16, !dbg !344
  br label %cond.end1303, !dbg !344

cond.end1303:                                     ; preds = %cond.false1300, %cond.true1266
  %cond1304 = phi i32 [ %add1299, %cond.true1266 ], [ %534, %cond.false1300 ], !dbg !345
  %add1305 = add i32 %add1264, %cond1304, !dbg !345
  %arrayidx1306 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !345
  %535 = load i32, i32* %arrayidx1306, align 4, !dbg !345
  %add1307 = add i32 %535, %add1305, !dbg !345
  store i32 %add1307, i32* %arrayidx1306, align 4, !dbg !345
  %arrayidx1308 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !345
  %536 = load i32, i32* %arrayidx1308, align 4, !dbg !345
  %arrayidx1309 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !345
  %537 = load i32, i32* %arrayidx1309, align 4, !dbg !345
  %add1310 = add i32 %537, %536, !dbg !345
  store i32 %add1310, i32* %arrayidx1309, align 4, !dbg !345
  %arrayidx1311 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %538 = load i32, i32* %arrayidx1311, align 16, !dbg !345
  %shr1312 = lshr i32 %538, 2, !dbg !345
  %arrayidx1313 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %539 = load i32, i32* %arrayidx1313, align 16, !dbg !345
  %shl1314 = shl i32 %539, 30, !dbg !345
  %or1315 = or i32 %shr1312, %shl1314, !dbg !345
  %arrayidx1316 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %540 = load i32, i32* %arrayidx1316, align 16, !dbg !345
  %shr1317 = lshr i32 %540, 13, !dbg !345
  %arrayidx1318 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %541 = load i32, i32* %arrayidx1318, align 16, !dbg !345
  %shl1319 = shl i32 %541, 19, !dbg !345
  %or1320 = or i32 %shr1317, %shl1319, !dbg !345
  %xor1321 = xor i32 %or1315, %or1320, !dbg !345
  %arrayidx1322 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %542 = load i32, i32* %arrayidx1322, align 16, !dbg !345
  %shr1323 = lshr i32 %542, 22, !dbg !345
  %arrayidx1324 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %543 = load i32, i32* %arrayidx1324, align 16, !dbg !345
  %shl1325 = shl i32 %543, 10, !dbg !345
  %or1326 = or i32 %shr1323, %shl1325, !dbg !345
  %xor1327 = xor i32 %xor1321, %or1326, !dbg !345
  %arrayidx1328 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %544 = load i32, i32* %arrayidx1328, align 16, !dbg !345
  %arrayidx1329 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !345
  %545 = load i32, i32* %arrayidx1329, align 4, !dbg !345
  %and1330 = and i32 %544, %545, !dbg !345
  %arrayidx1331 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !345
  %546 = load i32, i32* %arrayidx1331, align 8, !dbg !345
  %arrayidx1332 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !345
  %547 = load i32, i32* %arrayidx1332, align 16, !dbg !345
  %arrayidx1333 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !345
  %548 = load i32, i32* %arrayidx1333, align 4, !dbg !345
  %or1334 = or i32 %547, %548, !dbg !345
  %and1335 = and i32 %546, %or1334, !dbg !345
  %or1336 = or i32 %and1330, %and1335, !dbg !345
  %add1337 = add i32 %xor1327, %or1336, !dbg !345
  %arrayidx1338 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !345
  %549 = load i32, i32* %arrayidx1338, align 4, !dbg !345
  %add1339 = add i32 %549, %add1337, !dbg !345
  store i32 %add1339, i32* %arrayidx1338, align 4, !dbg !345
  %arrayidx1340 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %550 = load i32, i32* %arrayidx1340, align 4, !dbg !346
  %shr1341 = lshr i32 %550, 6, !dbg !346
  %arrayidx1342 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %551 = load i32, i32* %arrayidx1342, align 4, !dbg !346
  %shl1343 = shl i32 %551, 26, !dbg !346
  %or1344 = or i32 %shr1341, %shl1343, !dbg !346
  %arrayidx1345 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %552 = load i32, i32* %arrayidx1345, align 4, !dbg !346
  %shr1346 = lshr i32 %552, 11, !dbg !346
  %arrayidx1347 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %553 = load i32, i32* %arrayidx1347, align 4, !dbg !346
  %shl1348 = shl i32 %553, 21, !dbg !346
  %or1349 = or i32 %shr1346, %shl1348, !dbg !346
  %xor1350 = xor i32 %or1344, %or1349, !dbg !346
  %arrayidx1351 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %554 = load i32, i32* %arrayidx1351, align 4, !dbg !346
  %shr1352 = lshr i32 %554, 25, !dbg !346
  %arrayidx1353 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %555 = load i32, i32* %arrayidx1353, align 4, !dbg !346
  %shl1354 = shl i32 %555, 7, !dbg !346
  %or1355 = or i32 %shr1352, %shl1354, !dbg !346
  %xor1356 = xor i32 %xor1350, %or1355, !dbg !346
  %arrayidx1357 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !346
  %556 = load i32, i32* %arrayidx1357, align 4, !dbg !346
  %arrayidx1358 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !346
  %557 = load i32, i32* %arrayidx1358, align 4, !dbg !346
  %arrayidx1359 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !346
  %558 = load i32, i32* %arrayidx1359, align 16, !dbg !346
  %arrayidx1360 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !346
  %559 = load i32, i32* %arrayidx1360, align 4, !dbg !346
  %xor1361 = xor i32 %558, %559, !dbg !346
  %and1362 = and i32 %557, %xor1361, !dbg !346
  %xor1363 = xor i32 %556, %and1362, !dbg !346
  %add1364 = add i32 %xor1356, %xor1363, !dbg !346
  %560 = load i32, i32* %j, align 4, !dbg !346
  %add1365 = add i32 13, %560, !dbg !346
  %idxprom1366 = zext i32 %add1365 to i64, !dbg !346
  %arrayidx1367 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom1366, !dbg !346
  %561 = load i32, i32* %arrayidx1367, align 4, !dbg !346
  %add1368 = add i32 %add1364, %561, !dbg !346
  %562 = load i32, i32* %j, align 4, !dbg !346
  %tobool1369 = icmp ne i32 %562, 0, !dbg !346
  br i1 %tobool1369, label %cond.true1370, label %cond.false1404, !dbg !346

cond.true1370:                                    ; preds = %cond.end1303
  %arrayidx1371 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !347
  %563 = load i32, i32* %arrayidx1371, align 4, !dbg !347
  %shr1372 = lshr i32 %563, 17, !dbg !347
  %arrayidx1373 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !347
  %564 = load i32, i32* %arrayidx1373, align 4, !dbg !347
  %shl1374 = shl i32 %564, 15, !dbg !347
  %or1375 = or i32 %shr1372, %shl1374, !dbg !347
  %arrayidx1376 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !347
  %565 = load i32, i32* %arrayidx1376, align 4, !dbg !347
  %shr1377 = lshr i32 %565, 19, !dbg !347
  %arrayidx1378 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !347
  %566 = load i32, i32* %arrayidx1378, align 4, !dbg !347
  %shl1379 = shl i32 %566, 13, !dbg !347
  %or1380 = or i32 %shr1377, %shl1379, !dbg !347
  %xor1381 = xor i32 %or1375, %or1380, !dbg !347
  %arrayidx1382 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 11, !dbg !347
  %567 = load i32, i32* %arrayidx1382, align 4, !dbg !347
  %shr1383 = lshr i32 %567, 10, !dbg !347
  %xor1384 = xor i32 %xor1381, %shr1383, !dbg !347
  %arrayidx1385 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 6, !dbg !347
  %568 = load i32, i32* %arrayidx1385, align 8, !dbg !347
  %add1386 = add i32 %xor1384, %568, !dbg !347
  %arrayidx1387 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !347
  %569 = load i32, i32* %arrayidx1387, align 8, !dbg !347
  %shr1388 = lshr i32 %569, 7, !dbg !347
  %arrayidx1389 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !347
  %570 = load i32, i32* %arrayidx1389, align 8, !dbg !347
  %shl1390 = shl i32 %570, 25, !dbg !347
  %or1391 = or i32 %shr1388, %shl1390, !dbg !347
  %arrayidx1392 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !347
  %571 = load i32, i32* %arrayidx1392, align 8, !dbg !347
  %shr1393 = lshr i32 %571, 18, !dbg !347
  %arrayidx1394 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !347
  %572 = load i32, i32* %arrayidx1394, align 8, !dbg !347
  %shl1395 = shl i32 %572, 14, !dbg !347
  %or1396 = or i32 %shr1393, %shl1395, !dbg !347
  %xor1397 = xor i32 %or1391, %or1396, !dbg !347
  %arrayidx1398 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !347
  %573 = load i32, i32* %arrayidx1398, align 8, !dbg !347
  %shr1399 = lshr i32 %573, 3, !dbg !347
  %xor1400 = xor i32 %xor1397, %shr1399, !dbg !347
  %add1401 = add i32 %add1386, %xor1400, !dbg !347
  %arrayidx1402 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !347
  %574 = load i32, i32* %arrayidx1402, align 4, !dbg !347
  %add1403 = add i32 %574, %add1401, !dbg !347
  store i32 %add1403, i32* %arrayidx1402, align 4, !dbg !347
  br label %cond.end1407, !dbg !347

cond.false1404:                                   ; preds = %cond.end1303
  %575 = load i32*, i32** %data.addr, align 8, !dbg !348
  %arrayidx1405 = getelementptr inbounds i32, i32* %575, i64 13, !dbg !348
  %576 = load i32, i32* %arrayidx1405, align 4, !dbg !348
  %arrayidx1406 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !348
  store i32 %576, i32* %arrayidx1406, align 4, !dbg !348
  br label %cond.end1407, !dbg !348

cond.end1407:                                     ; preds = %cond.false1404, %cond.true1370
  %cond1408 = phi i32 [ %add1403, %cond.true1370 ], [ %576, %cond.false1404 ], !dbg !349
  %add1409 = add i32 %add1368, %cond1408, !dbg !349
  %arrayidx1410 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !349
  %577 = load i32, i32* %arrayidx1410, align 8, !dbg !349
  %add1411 = add i32 %577, %add1409, !dbg !349
  store i32 %add1411, i32* %arrayidx1410, align 8, !dbg !349
  %arrayidx1412 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !349
  %578 = load i32, i32* %arrayidx1412, align 8, !dbg !349
  %arrayidx1413 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !349
  %579 = load i32, i32* %arrayidx1413, align 8, !dbg !349
  %add1414 = add i32 %579, %578, !dbg !349
  store i32 %add1414, i32* %arrayidx1413, align 8, !dbg !349
  %arrayidx1415 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %580 = load i32, i32* %arrayidx1415, align 4, !dbg !349
  %shr1416 = lshr i32 %580, 2, !dbg !349
  %arrayidx1417 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %581 = load i32, i32* %arrayidx1417, align 4, !dbg !349
  %shl1418 = shl i32 %581, 30, !dbg !349
  %or1419 = or i32 %shr1416, %shl1418, !dbg !349
  %arrayidx1420 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %582 = load i32, i32* %arrayidx1420, align 4, !dbg !349
  %shr1421 = lshr i32 %582, 13, !dbg !349
  %arrayidx1422 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %583 = load i32, i32* %arrayidx1422, align 4, !dbg !349
  %shl1423 = shl i32 %583, 19, !dbg !349
  %or1424 = or i32 %shr1421, %shl1423, !dbg !349
  %xor1425 = xor i32 %or1419, %or1424, !dbg !349
  %arrayidx1426 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %584 = load i32, i32* %arrayidx1426, align 4, !dbg !349
  %shr1427 = lshr i32 %584, 22, !dbg !349
  %arrayidx1428 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %585 = load i32, i32* %arrayidx1428, align 4, !dbg !349
  %shl1429 = shl i32 %585, 10, !dbg !349
  %or1430 = or i32 %shr1427, %shl1429, !dbg !349
  %xor1431 = xor i32 %xor1425, %or1430, !dbg !349
  %arrayidx1432 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %586 = load i32, i32* %arrayidx1432, align 4, !dbg !349
  %arrayidx1433 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !349
  %587 = load i32, i32* %arrayidx1433, align 16, !dbg !349
  %and1434 = and i32 %586, %587, !dbg !349
  %arrayidx1435 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !349
  %588 = load i32, i32* %arrayidx1435, align 4, !dbg !349
  %arrayidx1436 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !349
  %589 = load i32, i32* %arrayidx1436, align 4, !dbg !349
  %arrayidx1437 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !349
  %590 = load i32, i32* %arrayidx1437, align 16, !dbg !349
  %or1438 = or i32 %589, %590, !dbg !349
  %and1439 = and i32 %588, %or1438, !dbg !349
  %or1440 = or i32 %and1434, %and1439, !dbg !349
  %add1441 = add i32 %xor1431, %or1440, !dbg !349
  %arrayidx1442 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !349
  %591 = load i32, i32* %arrayidx1442, align 8, !dbg !349
  %add1443 = add i32 %591, %add1441, !dbg !349
  store i32 %add1443, i32* %arrayidx1442, align 8, !dbg !349
  %arrayidx1444 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %592 = load i32, i32* %arrayidx1444, align 8, !dbg !350
  %shr1445 = lshr i32 %592, 6, !dbg !350
  %arrayidx1446 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %593 = load i32, i32* %arrayidx1446, align 8, !dbg !350
  %shl1447 = shl i32 %593, 26, !dbg !350
  %or1448 = or i32 %shr1445, %shl1447, !dbg !350
  %arrayidx1449 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %594 = load i32, i32* %arrayidx1449, align 8, !dbg !350
  %shr1450 = lshr i32 %594, 11, !dbg !350
  %arrayidx1451 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %595 = load i32, i32* %arrayidx1451, align 8, !dbg !350
  %shl1452 = shl i32 %595, 21, !dbg !350
  %or1453 = or i32 %shr1450, %shl1452, !dbg !350
  %xor1454 = xor i32 %or1448, %or1453, !dbg !350
  %arrayidx1455 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %596 = load i32, i32* %arrayidx1455, align 8, !dbg !350
  %shr1456 = lshr i32 %596, 25, !dbg !350
  %arrayidx1457 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %597 = load i32, i32* %arrayidx1457, align 8, !dbg !350
  %shl1458 = shl i32 %597, 7, !dbg !350
  %or1459 = or i32 %shr1456, %shl1458, !dbg !350
  %xor1460 = xor i32 %xor1454, %or1459, !dbg !350
  %arrayidx1461 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !350
  %598 = load i32, i32* %arrayidx1461, align 16, !dbg !350
  %arrayidx1462 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !350
  %599 = load i32, i32* %arrayidx1462, align 8, !dbg !350
  %arrayidx1463 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !350
  %600 = load i32, i32* %arrayidx1463, align 4, !dbg !350
  %arrayidx1464 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !350
  %601 = load i32, i32* %arrayidx1464, align 16, !dbg !350
  %xor1465 = xor i32 %600, %601, !dbg !350
  %and1466 = and i32 %599, %xor1465, !dbg !350
  %xor1467 = xor i32 %598, %and1466, !dbg !350
  %add1468 = add i32 %xor1460, %xor1467, !dbg !350
  %602 = load i32, i32* %j, align 4, !dbg !350
  %add1469 = add i32 14, %602, !dbg !350
  %idxprom1470 = zext i32 %add1469 to i64, !dbg !350
  %arrayidx1471 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom1470, !dbg !350
  %603 = load i32, i32* %arrayidx1471, align 4, !dbg !350
  %add1472 = add i32 %add1468, %603, !dbg !350
  %604 = load i32, i32* %j, align 4, !dbg !350
  %tobool1473 = icmp ne i32 %604, 0, !dbg !350
  br i1 %tobool1473, label %cond.true1474, label %cond.false1508, !dbg !350

cond.true1474:                                    ; preds = %cond.end1407
  %arrayidx1475 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !351
  %605 = load i32, i32* %arrayidx1475, align 16, !dbg !351
  %shr1476 = lshr i32 %605, 17, !dbg !351
  %arrayidx1477 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !351
  %606 = load i32, i32* %arrayidx1477, align 16, !dbg !351
  %shl1478 = shl i32 %606, 15, !dbg !351
  %or1479 = or i32 %shr1476, %shl1478, !dbg !351
  %arrayidx1480 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !351
  %607 = load i32, i32* %arrayidx1480, align 16, !dbg !351
  %shr1481 = lshr i32 %607, 19, !dbg !351
  %arrayidx1482 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !351
  %608 = load i32, i32* %arrayidx1482, align 16, !dbg !351
  %shl1483 = shl i32 %608, 13, !dbg !351
  %or1484 = or i32 %shr1481, %shl1483, !dbg !351
  %xor1485 = xor i32 %or1479, %or1484, !dbg !351
  %arrayidx1486 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 12, !dbg !351
  %609 = load i32, i32* %arrayidx1486, align 16, !dbg !351
  %shr1487 = lshr i32 %609, 10, !dbg !351
  %xor1488 = xor i32 %xor1485, %shr1487, !dbg !351
  %arrayidx1489 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 7, !dbg !351
  %610 = load i32, i32* %arrayidx1489, align 4, !dbg !351
  %add1490 = add i32 %xor1488, %610, !dbg !351
  %arrayidx1491 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !351
  %611 = load i32, i32* %arrayidx1491, align 4, !dbg !351
  %shr1492 = lshr i32 %611, 7, !dbg !351
  %arrayidx1493 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !351
  %612 = load i32, i32* %arrayidx1493, align 4, !dbg !351
  %shl1494 = shl i32 %612, 25, !dbg !351
  %or1495 = or i32 %shr1492, %shl1494, !dbg !351
  %arrayidx1496 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !351
  %613 = load i32, i32* %arrayidx1496, align 4, !dbg !351
  %shr1497 = lshr i32 %613, 18, !dbg !351
  %arrayidx1498 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !351
  %614 = load i32, i32* %arrayidx1498, align 4, !dbg !351
  %shl1499 = shl i32 %614, 14, !dbg !351
  %or1500 = or i32 %shr1497, %shl1499, !dbg !351
  %xor1501 = xor i32 %or1495, %or1500, !dbg !351
  %arrayidx1502 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !351
  %615 = load i32, i32* %arrayidx1502, align 4, !dbg !351
  %shr1503 = lshr i32 %615, 3, !dbg !351
  %xor1504 = xor i32 %xor1501, %shr1503, !dbg !351
  %add1505 = add i32 %add1490, %xor1504, !dbg !351
  %arrayidx1506 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !351
  %616 = load i32, i32* %arrayidx1506, align 8, !dbg !351
  %add1507 = add i32 %616, %add1505, !dbg !351
  store i32 %add1507, i32* %arrayidx1506, align 8, !dbg !351
  br label %cond.end1511, !dbg !351

cond.false1508:                                   ; preds = %cond.end1407
  %617 = load i32*, i32** %data.addr, align 8, !dbg !352
  %arrayidx1509 = getelementptr inbounds i32, i32* %617, i64 14, !dbg !352
  %618 = load i32, i32* %arrayidx1509, align 4, !dbg !352
  %arrayidx1510 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 14, !dbg !352
  store i32 %618, i32* %arrayidx1510, align 8, !dbg !352
  br label %cond.end1511, !dbg !352

cond.end1511:                                     ; preds = %cond.false1508, %cond.true1474
  %cond1512 = phi i32 [ %add1507, %cond.true1474 ], [ %618, %cond.false1508 ], !dbg !353
  %add1513 = add i32 %add1472, %cond1512, !dbg !353
  %arrayidx1514 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !353
  %619 = load i32, i32* %arrayidx1514, align 4, !dbg !353
  %add1515 = add i32 %619, %add1513, !dbg !353
  store i32 %add1515, i32* %arrayidx1514, align 4, !dbg !353
  %arrayidx1516 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !353
  %620 = load i32, i32* %arrayidx1516, align 4, !dbg !353
  %arrayidx1517 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !353
  %621 = load i32, i32* %arrayidx1517, align 4, !dbg !353
  %add1518 = add i32 %621, %620, !dbg !353
  store i32 %add1518, i32* %arrayidx1517, align 4, !dbg !353
  %arrayidx1519 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %622 = load i32, i32* %arrayidx1519, align 8, !dbg !353
  %shr1520 = lshr i32 %622, 2, !dbg !353
  %arrayidx1521 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %623 = load i32, i32* %arrayidx1521, align 8, !dbg !353
  %shl1522 = shl i32 %623, 30, !dbg !353
  %or1523 = or i32 %shr1520, %shl1522, !dbg !353
  %arrayidx1524 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %624 = load i32, i32* %arrayidx1524, align 8, !dbg !353
  %shr1525 = lshr i32 %624, 13, !dbg !353
  %arrayidx1526 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %625 = load i32, i32* %arrayidx1526, align 8, !dbg !353
  %shl1527 = shl i32 %625, 19, !dbg !353
  %or1528 = or i32 %shr1525, %shl1527, !dbg !353
  %xor1529 = xor i32 %or1523, %or1528, !dbg !353
  %arrayidx1530 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %626 = load i32, i32* %arrayidx1530, align 8, !dbg !353
  %shr1531 = lshr i32 %626, 22, !dbg !353
  %arrayidx1532 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %627 = load i32, i32* %arrayidx1532, align 8, !dbg !353
  %shl1533 = shl i32 %627, 10, !dbg !353
  %or1534 = or i32 %shr1531, %shl1533, !dbg !353
  %xor1535 = xor i32 %xor1529, %or1534, !dbg !353
  %arrayidx1536 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %628 = load i32, i32* %arrayidx1536, align 8, !dbg !353
  %arrayidx1537 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !353
  %629 = load i32, i32* %arrayidx1537, align 4, !dbg !353
  %and1538 = and i32 %628, %629, !dbg !353
  %arrayidx1539 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !353
  %630 = load i32, i32* %arrayidx1539, align 16, !dbg !353
  %arrayidx1540 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !353
  %631 = load i32, i32* %arrayidx1540, align 8, !dbg !353
  %arrayidx1541 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !353
  %632 = load i32, i32* %arrayidx1541, align 4, !dbg !353
  %or1542 = or i32 %631, %632, !dbg !353
  %and1543 = and i32 %630, %or1542, !dbg !353
  %or1544 = or i32 %and1538, %and1543, !dbg !353
  %add1545 = add i32 %xor1535, %or1544, !dbg !353
  %arrayidx1546 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !353
  %633 = load i32, i32* %arrayidx1546, align 4, !dbg !353
  %add1547 = add i32 %633, %add1545, !dbg !353
  store i32 %add1547, i32* %arrayidx1546, align 4, !dbg !353
  %arrayidx1548 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %634 = load i32, i32* %arrayidx1548, align 4, !dbg !354
  %shr1549 = lshr i32 %634, 6, !dbg !354
  %arrayidx1550 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %635 = load i32, i32* %arrayidx1550, align 4, !dbg !354
  %shl1551 = shl i32 %635, 26, !dbg !354
  %or1552 = or i32 %shr1549, %shl1551, !dbg !354
  %arrayidx1553 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %636 = load i32, i32* %arrayidx1553, align 4, !dbg !354
  %shr1554 = lshr i32 %636, 11, !dbg !354
  %arrayidx1555 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %637 = load i32, i32* %arrayidx1555, align 4, !dbg !354
  %shl1556 = shl i32 %637, 21, !dbg !354
  %or1557 = or i32 %shr1554, %shl1556, !dbg !354
  %xor1558 = xor i32 %or1552, %or1557, !dbg !354
  %arrayidx1559 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %638 = load i32, i32* %arrayidx1559, align 4, !dbg !354
  %shr1560 = lshr i32 %638, 25, !dbg !354
  %arrayidx1561 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %639 = load i32, i32* %arrayidx1561, align 4, !dbg !354
  %shl1562 = shl i32 %639, 7, !dbg !354
  %or1563 = or i32 %shr1560, %shl1562, !dbg !354
  %xor1564 = xor i32 %xor1558, %or1563, !dbg !354
  %arrayidx1565 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !354
  %640 = load i32, i32* %arrayidx1565, align 4, !dbg !354
  %arrayidx1566 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !354
  %641 = load i32, i32* %arrayidx1566, align 4, !dbg !354
  %arrayidx1567 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !354
  %642 = load i32, i32* %arrayidx1567, align 8, !dbg !354
  %arrayidx1568 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !354
  %643 = load i32, i32* %arrayidx1568, align 4, !dbg !354
  %xor1569 = xor i32 %642, %643, !dbg !354
  %and1570 = and i32 %641, %xor1569, !dbg !354
  %xor1571 = xor i32 %640, %and1570, !dbg !354
  %add1572 = add i32 %xor1564, %xor1571, !dbg !354
  %644 = load i32, i32* %j, align 4, !dbg !354
  %add1573 = add i32 15, %644, !dbg !354
  %idxprom1574 = zext i32 %add1573 to i64, !dbg !354
  %arrayidx1575 = getelementptr inbounds [64 x i32], [64 x i32]* @SHA256_K, i64 0, i64 %idxprom1574, !dbg !354
  %645 = load i32, i32* %arrayidx1575, align 4, !dbg !354
  %add1576 = add i32 %add1572, %645, !dbg !354
  %646 = load i32, i32* %j, align 4, !dbg !354
  %tobool1577 = icmp ne i32 %646, 0, !dbg !354
  br i1 %tobool1577, label %cond.true1578, label %cond.false1612, !dbg !354

cond.true1578:                                    ; preds = %cond.end1511
  %arrayidx1579 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !355
  %647 = load i32, i32* %arrayidx1579, align 4, !dbg !355
  %shr1580 = lshr i32 %647, 17, !dbg !355
  %arrayidx1581 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !355
  %648 = load i32, i32* %arrayidx1581, align 4, !dbg !355
  %shl1582 = shl i32 %648, 15, !dbg !355
  %or1583 = or i32 %shr1580, %shl1582, !dbg !355
  %arrayidx1584 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !355
  %649 = load i32, i32* %arrayidx1584, align 4, !dbg !355
  %shr1585 = lshr i32 %649, 19, !dbg !355
  %arrayidx1586 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !355
  %650 = load i32, i32* %arrayidx1586, align 4, !dbg !355
  %shl1587 = shl i32 %650, 13, !dbg !355
  %or1588 = or i32 %shr1585, %shl1587, !dbg !355
  %xor1589 = xor i32 %or1583, %or1588, !dbg !355
  %arrayidx1590 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 13, !dbg !355
  %651 = load i32, i32* %arrayidx1590, align 4, !dbg !355
  %shr1591 = lshr i32 %651, 10, !dbg !355
  %xor1592 = xor i32 %xor1589, %shr1591, !dbg !355
  %arrayidx1593 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 8, !dbg !355
  %652 = load i32, i32* %arrayidx1593, align 16, !dbg !355
  %add1594 = add i32 %xor1592, %652, !dbg !355
  %arrayidx1595 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !355
  %653 = load i32, i32* %arrayidx1595, align 16, !dbg !355
  %shr1596 = lshr i32 %653, 7, !dbg !355
  %arrayidx1597 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !355
  %654 = load i32, i32* %arrayidx1597, align 16, !dbg !355
  %shl1598 = shl i32 %654, 25, !dbg !355
  %or1599 = or i32 %shr1596, %shl1598, !dbg !355
  %arrayidx1600 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !355
  %655 = load i32, i32* %arrayidx1600, align 16, !dbg !355
  %shr1601 = lshr i32 %655, 18, !dbg !355
  %arrayidx1602 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !355
  %656 = load i32, i32* %arrayidx1602, align 16, !dbg !355
  %shl1603 = shl i32 %656, 14, !dbg !355
  %or1604 = or i32 %shr1601, %shl1603, !dbg !355
  %xor1605 = xor i32 %or1599, %or1604, !dbg !355
  %arrayidx1606 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 0, !dbg !355
  %657 = load i32, i32* %arrayidx1606, align 16, !dbg !355
  %shr1607 = lshr i32 %657, 3, !dbg !355
  %xor1608 = xor i32 %xor1605, %shr1607, !dbg !355
  %add1609 = add i32 %add1594, %xor1608, !dbg !355
  %arrayidx1610 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !355
  %658 = load i32, i32* %arrayidx1610, align 4, !dbg !355
  %add1611 = add i32 %658, %add1609, !dbg !355
  store i32 %add1611, i32* %arrayidx1610, align 4, !dbg !355
  br label %cond.end1615, !dbg !355

cond.false1612:                                   ; preds = %cond.end1511
  %659 = load i32*, i32** %data.addr, align 8, !dbg !356
  %arrayidx1613 = getelementptr inbounds i32, i32* %659, i64 15, !dbg !356
  %660 = load i32, i32* %arrayidx1613, align 4, !dbg !356
  %arrayidx1614 = getelementptr inbounds [16 x i32], [16 x i32]* %W, i64 0, i64 15, !dbg !356
  store i32 %660, i32* %arrayidx1614, align 4, !dbg !356
  br label %cond.end1615, !dbg !356

cond.end1615:                                     ; preds = %cond.false1612, %cond.true1578
  %cond1616 = phi i32 [ %add1611, %cond.true1578 ], [ %660, %cond.false1612 ], !dbg !357
  %add1617 = add i32 %add1576, %cond1616, !dbg !357
  %arrayidx1618 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !357
  %661 = load i32, i32* %arrayidx1618, align 16, !dbg !357
  %add1619 = add i32 %661, %add1617, !dbg !357
  store i32 %add1619, i32* %arrayidx1618, align 16, !dbg !357
  %arrayidx1620 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !357
  %662 = load i32, i32* %arrayidx1620, align 16, !dbg !357
  %arrayidx1621 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !357
  %663 = load i32, i32* %arrayidx1621, align 16, !dbg !357
  %add1622 = add i32 %663, %662, !dbg !357
  store i32 %add1622, i32* %arrayidx1621, align 16, !dbg !357
  %arrayidx1623 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %664 = load i32, i32* %arrayidx1623, align 4, !dbg !357
  %shr1624 = lshr i32 %664, 2, !dbg !357
  %arrayidx1625 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %665 = load i32, i32* %arrayidx1625, align 4, !dbg !357
  %shl1626 = shl i32 %665, 30, !dbg !357
  %or1627 = or i32 %shr1624, %shl1626, !dbg !357
  %arrayidx1628 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %666 = load i32, i32* %arrayidx1628, align 4, !dbg !357
  %shr1629 = lshr i32 %666, 13, !dbg !357
  %arrayidx1630 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %667 = load i32, i32* %arrayidx1630, align 4, !dbg !357
  %shl1631 = shl i32 %667, 19, !dbg !357
  %or1632 = or i32 %shr1629, %shl1631, !dbg !357
  %xor1633 = xor i32 %or1627, %or1632, !dbg !357
  %arrayidx1634 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %668 = load i32, i32* %arrayidx1634, align 4, !dbg !357
  %shr1635 = lshr i32 %668, 22, !dbg !357
  %arrayidx1636 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %669 = load i32, i32* %arrayidx1636, align 4, !dbg !357
  %shl1637 = shl i32 %669, 10, !dbg !357
  %or1638 = or i32 %shr1635, %shl1637, !dbg !357
  %xor1639 = xor i32 %xor1633, %or1638, !dbg !357
  %arrayidx1640 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %670 = load i32, i32* %arrayidx1640, align 4, !dbg !357
  %arrayidx1641 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !357
  %671 = load i32, i32* %arrayidx1641, align 8, !dbg !357
  %and1642 = and i32 %670, %671, !dbg !357
  %arrayidx1643 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !357
  %672 = load i32, i32* %arrayidx1643, align 4, !dbg !357
  %arrayidx1644 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !357
  %673 = load i32, i32* %arrayidx1644, align 4, !dbg !357
  %arrayidx1645 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !357
  %674 = load i32, i32* %arrayidx1645, align 8, !dbg !357
  %or1646 = or i32 %673, %674, !dbg !357
  %and1647 = and i32 %672, %or1646, !dbg !357
  %or1648 = or i32 %and1642, %and1647, !dbg !357
  %add1649 = add i32 %xor1639, %or1648, !dbg !357
  %arrayidx1650 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !357
  %675 = load i32, i32* %arrayidx1650, align 16, !dbg !357
  %add1651 = add i32 %675, %add1649, !dbg !357
  store i32 %add1651, i32* %arrayidx1650, align 16, !dbg !357
  br label %for.inc, !dbg !358

for.inc:                                          ; preds = %cond.end1615
  %676 = load i32, i32* %j, align 4, !dbg !359
  %add1652 = add i32 %676, 16, !dbg !359
  store i32 %add1652, i32* %j, align 4, !dbg !359
  br label %for.cond, !dbg !361

for.end:                                          ; preds = %for.cond
  %arrayidx1653 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 0, !dbg !362
  %677 = load i32, i32* %arrayidx1653, align 16, !dbg !362
  %678 = load i32*, i32** %state.addr, align 8, !dbg !363
  %arrayidx1654 = getelementptr inbounds i32, i32* %678, i64 0, !dbg !363
  %679 = load i32, i32* %arrayidx1654, align 4, !dbg !364
  %add1655 = add i32 %679, %677, !dbg !364
  store i32 %add1655, i32* %arrayidx1654, align 4, !dbg !364
  %arrayidx1656 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 1, !dbg !365
  %680 = load i32, i32* %arrayidx1656, align 4, !dbg !365
  %681 = load i32*, i32** %state.addr, align 8, !dbg !366
  %arrayidx1657 = getelementptr inbounds i32, i32* %681, i64 1, !dbg !366
  %682 = load i32, i32* %arrayidx1657, align 4, !dbg !367
  %add1658 = add i32 %682, %680, !dbg !367
  store i32 %add1658, i32* %arrayidx1657, align 4, !dbg !367
  %arrayidx1659 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 2, !dbg !368
  %683 = load i32, i32* %arrayidx1659, align 8, !dbg !368
  %684 = load i32*, i32** %state.addr, align 8, !dbg !369
  %arrayidx1660 = getelementptr inbounds i32, i32* %684, i64 2, !dbg !369
  %685 = load i32, i32* %arrayidx1660, align 4, !dbg !370
  %add1661 = add i32 %685, %683, !dbg !370
  store i32 %add1661, i32* %arrayidx1660, align 4, !dbg !370
  %arrayidx1662 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 3, !dbg !371
  %686 = load i32, i32* %arrayidx1662, align 4, !dbg !371
  %687 = load i32*, i32** %state.addr, align 8, !dbg !372
  %arrayidx1663 = getelementptr inbounds i32, i32* %687, i64 3, !dbg !372
  %688 = load i32, i32* %arrayidx1663, align 4, !dbg !373
  %add1664 = add i32 %688, %686, !dbg !373
  store i32 %add1664, i32* %arrayidx1663, align 4, !dbg !373
  %arrayidx1665 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 4, !dbg !374
  %689 = load i32, i32* %arrayidx1665, align 16, !dbg !374
  %690 = load i32*, i32** %state.addr, align 8, !dbg !375
  %arrayidx1666 = getelementptr inbounds i32, i32* %690, i64 4, !dbg !375
  %691 = load i32, i32* %arrayidx1666, align 4, !dbg !376
  %add1667 = add i32 %691, %689, !dbg !376
  store i32 %add1667, i32* %arrayidx1666, align 4, !dbg !376
  %arrayidx1668 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 5, !dbg !377
  %692 = load i32, i32* %arrayidx1668, align 4, !dbg !377
  %693 = load i32*, i32** %state.addr, align 8, !dbg !378
  %arrayidx1669 = getelementptr inbounds i32, i32* %693, i64 5, !dbg !378
  %694 = load i32, i32* %arrayidx1669, align 4, !dbg !379
  %add1670 = add i32 %694, %692, !dbg !379
  store i32 %add1670, i32* %arrayidx1669, align 4, !dbg !379
  %arrayidx1671 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 6, !dbg !380
  %695 = load i32, i32* %arrayidx1671, align 8, !dbg !380
  %696 = load i32*, i32** %state.addr, align 8, !dbg !381
  %arrayidx1672 = getelementptr inbounds i32, i32* %696, i64 6, !dbg !381
  %697 = load i32, i32* %arrayidx1672, align 4, !dbg !382
  %add1673 = add i32 %697, %695, !dbg !382
  store i32 %add1673, i32* %arrayidx1672, align 4, !dbg !382
  %arrayidx1674 = getelementptr inbounds [8 x i32], [8 x i32]* %T, i64 0, i64 7, !dbg !383
  %698 = load i32, i32* %arrayidx1674, align 4, !dbg !383
  %699 = load i32*, i32** %state.addr, align 8, !dbg !384
  %arrayidx1675 = getelementptr inbounds i32, i32* %699, i64 7, !dbg !384
  %700 = load i32, i32* %arrayidx1675, align 4, !dbg !385
  %add1676 = add i32 %700, %698, !dbg !385
  store i32 %add1676, i32* %arrayidx1675, align 4, !dbg !385
  ret void, !dbg !386
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!65, !66}
!llvm.ident = !{!67}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !60)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/sha256.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{}
!3 = !{!4, !45, !52, !53, !54}
!4 = distinct !DISubprogram(name: "lzma_sha256_init", scope: !1, file: !1, line: 133, type: !5, isLocal: false, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null, !7}
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check_state", file: !9, line: 56, baseType: !10)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!10 = !DICompositeType(tag: DW_TAG_structure_type, file: !9, line: 34, size: 832, align: 64, elements: !11)
!11 = !{!12, !34}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !10, file: !9, line: 40, baseType: !13, size: 512, align: 64)
!13 = !DICompositeType(tag: DW_TAG_union_type, scope: !10, file: !9, line: 36, size: 512, align: 64, elements: !14)
!14 = !{!15, !22, !28}
!15 = !DIDerivedType(tag: DW_TAG_member, name: "u8", scope: !13, file: !9, line: 37, baseType: !16, size: 512, align: 8)
!16 = !DICompositeType(tag: DW_TAG_array_type, baseType: !17, size: 512, align: 8, elements: !20)
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !18, line: 48, baseType: !19)
!18 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!19 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!20 = !{!21}
!21 = !DISubrange(count: 64)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "u32", scope: !13, file: !9, line: 38, baseType: !23, size: 512, align: 32)
!23 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 512, align: 32, elements: !26)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !18, line: 51, baseType: !25)
!25 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!26 = !{!27}
!27 = !DISubrange(count: 16)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "u64", scope: !13, file: !9, line: 39, baseType: !29, size: 512, align: 64)
!29 = !DICompositeType(tag: DW_TAG_array_type, baseType: !30, size: 512, align: 64, elements: !32)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !18, line: 55, baseType: !31)
!31 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!32 = !{!33}
!33 = !DISubrange(count: 8)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !10, file: !9, line: 54, baseType: !35, size: 320, align: 64, offset: 512)
!35 = !DICompositeType(tag: DW_TAG_union_type, scope: !10, file: !9, line: 43, size: 320, align: 64, elements: !36)
!36 = !{!37, !38, !39}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !35, file: !9, line: 44, baseType: !24, size: 32, align: 32)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "crc64", scope: !35, file: !9, line: 45, baseType: !30, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "sha256", scope: !35, file: !9, line: 53, baseType: !40, size: 320, align: 64)
!40 = !DICompositeType(tag: DW_TAG_structure_type, scope: !35, file: !9, line: 47, size: 320, align: 64, elements: !41)
!41 = !{!42, !44}
!42 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !40, file: !9, line: 49, baseType: !43, size: 256, align: 32)
!43 = !DICompositeType(tag: DW_TAG_array_type, baseType: !24, size: 256, align: 32, elements: !32)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !40, file: !9, line: 52, baseType: !30, size: 64, align: 64, offset: 256)
!45 = distinct !DISubprogram(name: "lzma_sha256_update", scope: !1, file: !1, line: 148, type: !46, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!46 = !DISubroutineType(types: !47)
!47 = !{null, !48, !50, !7}
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !17)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !51, line: 62, baseType: !31)
!51 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!52 = distinct !DISubprogram(name: "lzma_sha256_finish", scope: !1, file: !1, line: 175, type: !5, isLocal: false, isDefinition: true, scopeLine: 176, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!53 = distinct !DISubprogram(name: "process", scope: !1, file: !1, line: 113, type: !5, isLocal: true, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!54 = distinct !DISubprogram(name: "transform", scope: !1, file: !1, line: 83, type: !55, isLocal: true, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!55 = !DISubroutineType(types: !56)
!56 = !{null, !57, !58}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !24)
!60 = !{!61, !63}
!61 = !DIGlobalVariable(name: "s", scope: !4, file: !1, line: 135, type: !62, isLocal: true, isDefinition: true, variable: [8 x i32]* @lzma_sha256_init.s)
!62 = !DICompositeType(tag: DW_TAG_array_type, baseType: !59, size: 256, align: 32, elements: !32)
!63 = !DIGlobalVariable(name: "SHA256_K", scope: !0, file: !1, line: 62, type: !64, isLocal: true, isDefinition: true, variable: [64 x i32]* @SHA256_K)
!64 = !DICompositeType(tag: DW_TAG_array_type, baseType: !59, size: 2048, align: 32, elements: !20)
!65 = !{i32 2, !"Dwarf Version", i32 4}
!66 = !{i32 2, !"Debug Info Version", i32 3}
!67 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!68 = !DILocalVariable(name: "check", arg: 1, scope: !4, file: !1, line: 133, type: !7)
!69 = !DIExpression()
!70 = !DILocation(line: 133, column: 36, scope: !4)
!71 = !DILocation(line: 140, column: 9, scope: !4)
!72 = !DILocation(line: 140, column: 16, scope: !4)
!73 = !DILocation(line: 140, column: 22, scope: !4)
!74 = !DILocation(line: 140, column: 29, scope: !4)
!75 = !DILocation(line: 140, column: 2, scope: !4)
!76 = !DILocation(line: 141, column: 2, scope: !4)
!77 = !DILocation(line: 141, column: 9, scope: !4)
!78 = !DILocation(line: 141, column: 15, scope: !4)
!79 = !DILocation(line: 141, column: 22, scope: !4)
!80 = !DILocation(line: 141, column: 27, scope: !4)
!81 = !DILocation(line: 143, column: 2, scope: !4)
!82 = !DILocalVariable(name: "buf", arg: 1, scope: !45, file: !1, line: 148, type: !48)
!83 = !DILocation(line: 148, column: 35, scope: !45)
!84 = !DILocalVariable(name: "size", arg: 2, scope: !45, file: !1, line: 148, type: !50)
!85 = !DILocation(line: 148, column: 47, scope: !45)
!86 = !DILocalVariable(name: "check", arg: 3, scope: !45, file: !1, line: 148, type: !7)
!87 = !DILocation(line: 148, column: 71, scope: !45)
!88 = !DILocation(line: 154, column: 2, scope: !45)
!89 = !DILocation(line: 154, column: 9, scope: !90)
!90 = !DILexicalBlockFile(scope: !45, file: !1, discriminator: 1)
!91 = !DILocation(line: 154, column: 14, scope: !90)
!92 = !DILocation(line: 154, column: 2, scope: !90)
!93 = !DILocalVariable(name: "copy_start", scope: !94, file: !1, line: 155, type: !95)
!94 = distinct !DILexicalBlock(scope: !45, file: !1, line: 154, column: 19)
!95 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !50)
!96 = !DILocation(line: 155, column: 16, scope: !94)
!97 = !DILocation(line: 155, column: 29, scope: !94)
!98 = !DILocation(line: 155, column: 36, scope: !94)
!99 = !DILocation(line: 155, column: 42, scope: !94)
!100 = !DILocation(line: 155, column: 49, scope: !94)
!101 = !DILocation(line: 155, column: 54, scope: !94)
!102 = !DILocalVariable(name: "copy_size", scope: !94, file: !1, line: 156, type: !50)
!103 = !DILocation(line: 156, column: 10, scope: !94)
!104 = !DILocation(line: 156, column: 27, scope: !94)
!105 = !DILocation(line: 156, column: 25, scope: !94)
!106 = !DILocation(line: 157, column: 7, scope: !107)
!107 = distinct !DILexicalBlock(scope: !94, file: !1, line: 157, column: 7)
!108 = !DILocation(line: 157, column: 19, scope: !107)
!109 = !DILocation(line: 157, column: 17, scope: !107)
!110 = !DILocation(line: 157, column: 7, scope: !94)
!111 = !DILocation(line: 158, column: 16, scope: !107)
!112 = !DILocation(line: 158, column: 14, scope: !107)
!113 = !DILocation(line: 158, column: 4, scope: !107)
!114 = !DILocation(line: 160, column: 10, scope: !94)
!115 = !DILocation(line: 160, column: 17, scope: !94)
!116 = !DILocation(line: 160, column: 24, scope: !94)
!117 = !DILocation(line: 160, column: 29, scope: !94)
!118 = !DILocation(line: 160, column: 27, scope: !94)
!119 = !DILocation(line: 160, column: 41, scope: !94)
!120 = !DILocation(line: 160, column: 46, scope: !94)
!121 = !DILocation(line: 160, column: 3, scope: !94)
!122 = !DILocation(line: 162, column: 10, scope: !94)
!123 = !DILocation(line: 162, column: 7, scope: !94)
!124 = !DILocation(line: 163, column: 11, scope: !94)
!125 = !DILocation(line: 163, column: 8, scope: !94)
!126 = !DILocation(line: 164, column: 31, scope: !94)
!127 = !DILocation(line: 164, column: 3, scope: !94)
!128 = !DILocation(line: 164, column: 10, scope: !94)
!129 = !DILocation(line: 164, column: 16, scope: !94)
!130 = !DILocation(line: 164, column: 23, scope: !94)
!131 = !DILocation(line: 164, column: 28, scope: !94)
!132 = !DILocation(line: 166, column: 8, scope: !133)
!133 = distinct !DILexicalBlock(scope: !94, file: !1, line: 166, column: 7)
!134 = !DILocation(line: 166, column: 15, scope: !133)
!135 = !DILocation(line: 166, column: 21, scope: !133)
!136 = !DILocation(line: 166, column: 28, scope: !133)
!137 = !DILocation(line: 166, column: 33, scope: !133)
!138 = !DILocation(line: 166, column: 41, scope: !133)
!139 = !DILocation(line: 166, column: 7, scope: !94)
!140 = !DILocation(line: 167, column: 12, scope: !133)
!141 = !DILocation(line: 167, column: 4, scope: !133)
!142 = !DILocation(line: 154, column: 2, scope: !143)
!143 = !DILexicalBlockFile(scope: !45, file: !1, discriminator: 2)
!144 = !DILocation(line: 170, column: 2, scope: !45)
!145 = !DILocalVariable(name: "check", arg: 1, scope: !53, file: !1, line: 113, type: !7)
!146 = !DILocation(line: 113, column: 27, scope: !53)
!147 = !DILocalVariable(name: "data", scope: !53, file: !1, line: 119, type: !23)
!148 = !DILocation(line: 119, column: 11, scope: !53)
!149 = !DILocalVariable(name: "i", scope: !53, file: !1, line: 120, type: !50)
!150 = !DILocation(line: 120, column: 9, scope: !53)
!151 = !DILocation(line: 122, column: 9, scope: !152)
!152 = distinct !DILexicalBlock(scope: !53, file: !1, line: 122, column: 2)
!153 = !DILocation(line: 122, column: 7, scope: !152)
!154 = !DILocation(line: 122, column: 14, scope: !155)
!155 = !DILexicalBlockFile(scope: !156, file: !1, discriminator: 1)
!156 = distinct !DILexicalBlock(scope: !152, file: !1, line: 122, column: 2)
!157 = !DILocation(line: 122, column: 16, scope: !155)
!158 = !DILocation(line: 122, column: 2, scope: !155)
!159 = !DILocalVariable(name: "__v", scope: !160, file: !1, line: 123, type: !25)
!160 = distinct !DILexicalBlock(scope: !156, file: !1, line: 123, column: 13)
!161 = !DILocation(line: 123, column: 13, scope: !160)
!162 = !DILocalVariable(name: "__x", scope: !160, file: !1, line: 123, type: !25)
!163 = !DILocation(line: 123, column: 13, scope: !164)
!164 = distinct !DILexicalBlock(scope: !160, file: !1, line: 123, column: 13)
!165 = !{i32 -2146911981}
!166 = !DILocation(line: 123, column: 8, scope: !156)
!167 = !DILocation(line: 123, column: 3, scope: !156)
!168 = !DILocation(line: 123, column: 11, scope: !156)
!169 = !DILocation(line: 122, column: 22, scope: !170)
!170 = !DILexicalBlockFile(scope: !156, file: !1, discriminator: 2)
!171 = !DILocation(line: 122, column: 2, scope: !170)
!172 = !DILocation(line: 125, column: 12, scope: !53)
!173 = !DILocation(line: 125, column: 19, scope: !53)
!174 = !DILocation(line: 125, column: 25, scope: !53)
!175 = !DILocation(line: 125, column: 32, scope: !53)
!176 = !DILocation(line: 125, column: 39, scope: !53)
!177 = !DILocation(line: 125, column: 2, scope: !53)
!178 = !DILocation(line: 128, column: 2, scope: !53)
!179 = !DILocalVariable(name: "check", arg: 1, scope: !52, file: !1, line: 175, type: !7)
!180 = !DILocation(line: 175, column: 38, scope: !52)
!181 = !DILocalVariable(name: "i", scope: !52, file: !1, line: 177, type: !50)
!182 = !DILocation(line: 177, column: 9, scope: !52)
!183 = !DILocalVariable(name: "pos", scope: !52, file: !1, line: 181, type: !50)
!184 = !DILocation(line: 181, column: 9, scope: !52)
!185 = !DILocation(line: 181, column: 15, scope: !52)
!186 = !DILocation(line: 181, column: 22, scope: !52)
!187 = !DILocation(line: 181, column: 28, scope: !52)
!188 = !DILocation(line: 181, column: 35, scope: !52)
!189 = !DILocation(line: 181, column: 40, scope: !52)
!190 = !DILocation(line: 182, column: 22, scope: !52)
!191 = !DILocation(line: 182, column: 2, scope: !52)
!192 = !DILocation(line: 182, column: 9, scope: !52)
!193 = !DILocation(line: 182, column: 16, scope: !52)
!194 = !DILocation(line: 182, column: 26, scope: !52)
!195 = !DILocation(line: 184, column: 2, scope: !52)
!196 = !DILocation(line: 184, column: 9, scope: !197)
!197 = !DILexicalBlockFile(scope: !52, file: !1, discriminator: 1)
!198 = !DILocation(line: 184, column: 13, scope: !197)
!199 = !DILocation(line: 184, column: 2, scope: !197)
!200 = !DILocation(line: 185, column: 7, scope: !201)
!201 = distinct !DILexicalBlock(scope: !202, file: !1, line: 185, column: 7)
!202 = distinct !DILexicalBlock(scope: !52, file: !1, line: 184, column: 24)
!203 = !DILocation(line: 185, column: 11, scope: !201)
!204 = !DILocation(line: 185, column: 7, scope: !202)
!205 = !DILocation(line: 186, column: 12, scope: !206)
!206 = distinct !DILexicalBlock(scope: !201, file: !1, line: 185, column: 18)
!207 = !DILocation(line: 186, column: 4, scope: !206)
!208 = !DILocation(line: 187, column: 8, scope: !206)
!209 = !DILocation(line: 188, column: 3, scope: !206)
!210 = !DILocation(line: 190, column: 23, scope: !202)
!211 = !DILocation(line: 190, column: 3, scope: !202)
!212 = !DILocation(line: 190, column: 10, scope: !202)
!213 = !DILocation(line: 190, column: 17, scope: !202)
!214 = !DILocation(line: 190, column: 27, scope: !202)
!215 = !DILocation(line: 184, column: 2, scope: !216)
!216 = !DILexicalBlockFile(scope: !52, file: !1, discriminator: 2)
!217 = !DILocation(line: 194, column: 2, scope: !52)
!218 = !DILocation(line: 194, column: 9, scope: !52)
!219 = !DILocation(line: 194, column: 15, scope: !52)
!220 = !DILocation(line: 194, column: 22, scope: !52)
!221 = !DILocation(line: 194, column: 27, scope: !52)
!222 = !DILocalVariable(name: "__v", scope: !223, file: !1, line: 196, type: !224)
!223 = distinct !DILexicalBlock(scope: !52, file: !1, line: 196, column: 36)
!224 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint64_t", file: !225, line: 44, baseType: !31)
!225 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!226 = !DILocation(line: 196, column: 36, scope: !223)
!227 = !DILocalVariable(name: "__x", scope: !223, file: !1, line: 196, type: !224)
!228 = !DILocation(line: 196, column: 36, scope: !229)
!229 = distinct !DILexicalBlock(scope: !223, file: !1, line: 196, column: 36)
!230 = !{i32 -2146911432}
!231 = !DILocation(line: 196, column: 2, scope: !52)
!232 = !DILocation(line: 196, column: 9, scope: !52)
!233 = !DILocation(line: 196, column: 16, scope: !52)
!234 = !DILocation(line: 196, column: 34, scope: !52)
!235 = !DILocation(line: 198, column: 10, scope: !52)
!236 = !DILocation(line: 198, column: 2, scope: !52)
!237 = !DILocation(line: 200, column: 9, scope: !238)
!238 = distinct !DILexicalBlock(scope: !52, file: !1, line: 200, column: 2)
!239 = !DILocation(line: 200, column: 7, scope: !238)
!240 = !DILocation(line: 200, column: 14, scope: !241)
!241 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 1)
!242 = distinct !DILexicalBlock(scope: !238, file: !1, line: 200, column: 2)
!243 = !DILocation(line: 200, column: 16, scope: !241)
!244 = !DILocation(line: 200, column: 2, scope: !241)
!245 = !DILocalVariable(name: "__v", scope: !246, file: !1, line: 201, type: !25)
!246 = distinct !DILexicalBlock(scope: !242, file: !1, line: 201, column: 26)
!247 = !DILocation(line: 201, column: 26, scope: !246)
!248 = !DILocalVariable(name: "__x", scope: !246, file: !1, line: 201, type: !25)
!249 = !DILocation(line: 201, column: 26, scope: !250)
!250 = distinct !DILexicalBlock(scope: !246, file: !1, line: 201, column: 26)
!251 = !{i32 -2146910529}
!252 = !DILocation(line: 201, column: 21, scope: !242)
!253 = !DILocation(line: 201, column: 3, scope: !242)
!254 = !DILocation(line: 201, column: 10, scope: !242)
!255 = !DILocation(line: 201, column: 17, scope: !242)
!256 = !DILocation(line: 201, column: 24, scope: !242)
!257 = !DILocation(line: 200, column: 21, scope: !258)
!258 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 2)
!259 = !DILocation(line: 200, column: 2, scope: !258)
!260 = !DILocation(line: 203, column: 2, scope: !52)
!261 = !DILocalVariable(name: "state", arg: 1, scope: !54, file: !1, line: 83, type: !57)
!262 = !DILocation(line: 83, column: 20, scope: !54)
!263 = !DILocalVariable(name: "data", arg: 2, scope: !54, file: !1, line: 83, type: !58)
!264 = !DILocation(line: 83, column: 45, scope: !54)
!265 = !DILocalVariable(name: "W", scope: !54, file: !1, line: 85, type: !23)
!266 = !DILocation(line: 85, column: 11, scope: !54)
!267 = !DILocalVariable(name: "T", scope: !54, file: !1, line: 86, type: !43)
!268 = !DILocation(line: 86, column: 11, scope: !54)
!269 = !DILocalVariable(name: "j", scope: !54, file: !1, line: 87, type: !25)
!270 = !DILocation(line: 87, column: 15, scope: !54)
!271 = !DILocation(line: 90, column: 2, scope: !54)
!272 = !DILocation(line: 90, column: 12, scope: !54)
!273 = !DILocation(line: 93, column: 9, scope: !274)
!274 = distinct !DILexicalBlock(scope: !54, file: !1, line: 93, column: 2)
!275 = !DILocation(line: 93, column: 7, scope: !274)
!276 = !DILocation(line: 93, column: 14, scope: !277)
!277 = !DILexicalBlockFile(scope: !278, file: !1, discriminator: 1)
!278 = distinct !DILexicalBlock(scope: !274, file: !1, line: 93, column: 2)
!279 = !DILocation(line: 93, column: 16, scope: !277)
!280 = !DILocation(line: 93, column: 2, scope: !277)
!281 = !DILocation(line: 94, column: 3, scope: !282)
!282 = distinct !DILexicalBlock(scope: !278, file: !1, line: 93, column: 31)
!283 = !DILocation(line: 94, column: 3, scope: !284)
!284 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 1)
!285 = !DILocation(line: 94, column: 3, scope: !286)
!286 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 2)
!287 = !DILocation(line: 94, column: 3, scope: !288)
!288 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 3)
!289 = !DILocation(line: 94, column: 10, scope: !288)
!290 = !DILocation(line: 94, column: 10, scope: !291)
!291 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 4)
!292 = !DILocation(line: 94, column: 10, scope: !293)
!293 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 5)
!294 = !DILocation(line: 94, column: 10, scope: !295)
!295 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 6)
!296 = !DILocation(line: 94, column: 17, scope: !295)
!297 = !DILocation(line: 94, column: 17, scope: !298)
!298 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 7)
!299 = !DILocation(line: 94, column: 17, scope: !300)
!300 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 8)
!301 = !DILocation(line: 94, column: 17, scope: !302)
!302 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 9)
!303 = !DILocation(line: 94, column: 24, scope: !302)
!304 = !DILocation(line: 94, column: 24, scope: !305)
!305 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 10)
!306 = !DILocation(line: 94, column: 24, scope: !307)
!307 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 11)
!308 = !DILocation(line: 94, column: 24, scope: !309)
!309 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 12)
!310 = !DILocation(line: 95, column: 3, scope: !282)
!311 = !DILocation(line: 95, column: 3, scope: !284)
!312 = !DILocation(line: 95, column: 3, scope: !286)
!313 = !DILocation(line: 95, column: 3, scope: !288)
!314 = !DILocation(line: 95, column: 10, scope: !288)
!315 = !DILocation(line: 95, column: 10, scope: !291)
!316 = !DILocation(line: 95, column: 10, scope: !293)
!317 = !DILocation(line: 95, column: 10, scope: !295)
!318 = !DILocation(line: 95, column: 17, scope: !295)
!319 = !DILocation(line: 95, column: 17, scope: !298)
!320 = !DILocation(line: 95, column: 17, scope: !300)
!321 = !DILocation(line: 95, column: 17, scope: !302)
!322 = !DILocation(line: 95, column: 24, scope: !302)
!323 = !DILocation(line: 95, column: 24, scope: !305)
!324 = !DILocation(line: 95, column: 24, scope: !307)
!325 = !DILocation(line: 95, column: 24, scope: !309)
!326 = !DILocation(line: 96, column: 3, scope: !282)
!327 = !DILocation(line: 96, column: 3, scope: !284)
!328 = !DILocation(line: 96, column: 3, scope: !286)
!329 = !DILocation(line: 96, column: 3, scope: !288)
!330 = !DILocation(line: 96, column: 10, scope: !288)
!331 = !DILocation(line: 96, column: 10, scope: !291)
!332 = !DILocation(line: 96, column: 10, scope: !293)
!333 = !DILocation(line: 96, column: 10, scope: !295)
!334 = !DILocation(line: 96, column: 17, scope: !295)
!335 = !DILocation(line: 96, column: 17, scope: !298)
!336 = !DILocation(line: 96, column: 17, scope: !300)
!337 = !DILocation(line: 96, column: 17, scope: !302)
!338 = !DILocation(line: 96, column: 24, scope: !302)
!339 = !DILocation(line: 96, column: 24, scope: !305)
!340 = !DILocation(line: 96, column: 24, scope: !307)
!341 = !DILocation(line: 96, column: 24, scope: !309)
!342 = !DILocation(line: 97, column: 3, scope: !282)
!343 = !DILocation(line: 97, column: 3, scope: !284)
!344 = !DILocation(line: 97, column: 3, scope: !286)
!345 = !DILocation(line: 97, column: 3, scope: !288)
!346 = !DILocation(line: 97, column: 10, scope: !288)
!347 = !DILocation(line: 97, column: 10, scope: !291)
!348 = !DILocation(line: 97, column: 10, scope: !293)
!349 = !DILocation(line: 97, column: 10, scope: !295)
!350 = !DILocation(line: 97, column: 17, scope: !295)
!351 = !DILocation(line: 97, column: 17, scope: !298)
!352 = !DILocation(line: 97, column: 17, scope: !300)
!353 = !DILocation(line: 97, column: 17, scope: !302)
!354 = !DILocation(line: 97, column: 24, scope: !302)
!355 = !DILocation(line: 97, column: 24, scope: !305)
!356 = !DILocation(line: 97, column: 24, scope: !307)
!357 = !DILocation(line: 97, column: 24, scope: !309)
!358 = !DILocation(line: 98, column: 2, scope: !282)
!359 = !DILocation(line: 93, column: 24, scope: !360)
!360 = !DILexicalBlockFile(scope: !278, file: !1, discriminator: 2)
!361 = !DILocation(line: 93, column: 2, scope: !360)
!362 = !DILocation(line: 101, column: 14, scope: !54)
!363 = !DILocation(line: 101, column: 2, scope: !54)
!364 = !DILocation(line: 101, column: 11, scope: !54)
!365 = !DILocation(line: 102, column: 14, scope: !54)
!366 = !DILocation(line: 102, column: 2, scope: !54)
!367 = !DILocation(line: 102, column: 11, scope: !54)
!368 = !DILocation(line: 103, column: 14, scope: !54)
!369 = !DILocation(line: 103, column: 2, scope: !54)
!370 = !DILocation(line: 103, column: 11, scope: !54)
!371 = !DILocation(line: 104, column: 14, scope: !54)
!372 = !DILocation(line: 104, column: 2, scope: !54)
!373 = !DILocation(line: 104, column: 11, scope: !54)
!374 = !DILocation(line: 105, column: 14, scope: !54)
!375 = !DILocation(line: 105, column: 2, scope: !54)
!376 = !DILocation(line: 105, column: 11, scope: !54)
!377 = !DILocation(line: 106, column: 14, scope: !54)
!378 = !DILocation(line: 106, column: 2, scope: !54)
!379 = !DILocation(line: 106, column: 11, scope: !54)
!380 = !DILocation(line: 107, column: 14, scope: !54)
!381 = !DILocation(line: 107, column: 2, scope: !54)
!382 = !DILocation(line: 107, column: 11, scope: !54)
!383 = !DILocation(line: 108, column: 14, scope: !54)
!384 = !DILocation(line: 108, column: 2, scope: !54)
!385 = !DILocation(line: 108, column: 11, scope: !54)
!386 = !DILocation(line: 109, column: 1, scope: !54)
